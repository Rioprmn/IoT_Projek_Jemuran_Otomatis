#include <WiFi.h>
#include <ESP32Servo.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// ===================== WiFi =====================
const char* ssid     = "KostVanJava";
const char* password = "1januari";

// ===================== MQTT =====================
const char* mqttServer   = "232cc13511a94d45a753f80dd7e48363.s1.eu.hivemq.cloud";
const int   mqttPort     = 8883;
const char* mqttUser     = "esp32user";
const char* mqttPassword = "esp32Pass123";
const char* clientID     = "ESP32-AtapJemuran";

// Topic
const char* topicStatus  = "atap/status";   // ESP32 publish
const char* topicKontrol = "atap/kontrol";  // ESP32 subscribe
const char* topicMode    = "atap/mode";     // ESP32 subscribe

// ===================== Pin =====================
const int pinServo  = 13;
const int pinRainDO = 14;
const int pinLDRAo  = 35;

// ===================== Servo =====================
const int posisiTutup = 90;
const int posisiBuka  = 0;

// ===================== Threshold =====================
const int batasMendung = 2500;

// ===================== Debounce =====================
const unsigned long durasiKonfirmasi = 1500;

Servo myservo;
WiFiClientSecure espClient;
PubSubClient mqttClient(espClient);

// ===================== Shared Data =====================
SemaphoreHandle_t mutexData;
SemaphoreHandle_t mutexServo;

volatile int g_statusHujan    = 1;   // 1=kering, 0=hujan
volatile int g_nilaiLDR       = 0;
volatile int g_statusAtap     = -1;  // 0=buka, 1=tutup
volatile int g_mode           = 0;   // 0=AUTO, 1=MANUAL
volatile int g_perintahManual = -1;  // 0=buka, 1=tutup

// =====================================================
// MQTT CALLBACK — terima perintah dari web
// =====================================================
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String pesan = "";
  for (int i = 0; i < length; i++) {
    pesan += (char)payload[i];
  }

  Serial.print("[MQTT] Topic: "); Serial.print(topic);
  Serial.print(" | Pesan: "); Serial.println(pesan);

  if (String(topic) == topicMode) {
    if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
      if (pesan == "AUTO")   g_mode = 0;
      if (pesan == "MANUAL") g_mode = 1;
      xSemaphoreGive(mutexData);
    }
  }

  if (String(topic) == topicKontrol) {
    if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
      if (pesan == "BUKA")  g_perintahManual = 0;
      if (pesan == "TUTUP") g_perintahManual = 1;
      xSemaphoreGive(mutexData);
    }
  }
}

// =====================================================
// TASK WIFI
// =====================================================
void TaskWiFi(void *parameter) {

  WiFi.mode(WIFI_STA);
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }

  Serial.println();
  Serial.println("==============================");
  Serial.println("WiFi Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  Serial.println("==============================");

  for (;;) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi Terputus! Reconnect...");
      WiFi.disconnect(true);
      WiFi.begin(ssid, password);

      int percobaan = 0;
      while (WiFi.status() != WL_CONNECTED && percobaan < 20) {
        Serial.print(".");
        vTaskDelay(500 / portTICK_PERIOD_MS);
        percobaan++;
      }

      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nReconnect Berhasil");
      } else {
        Serial.println("\nReconnect Gagal");
      }
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

// =====================================================
// TASK MQTT
// =====================================================
void TaskMQTT(void *parameter) {

  espClient.setInsecure(); // skip verifikasi sertifikat

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
  mqttClient.setKeepAlive(60);
  mqttClient.setBufferSize(512);

  // Tunggu WiFi dulu
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }

  for (;;) {

    if (!mqttClient.connected()) {
      Serial.println("[MQTT] Connecting...");

      if (mqttClient.connect(clientID, mqttUser, mqttPassword)) {
        Serial.println("[MQTT] Connected!");

        // Subscribe topic kontrol & mode
        mqttClient.subscribe(topicKontrol);
        mqttClient.subscribe(topicMode);
        Serial.println("[MQTT] Subscribed ke atap/kontrol & atap/mode");

      } else {
        Serial.print("[MQTT] Gagal, rc=");
        Serial.println(mqttClient.state());
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        continue;
      }
    }

    mqttClient.loop();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

// =====================================================
// TASK PUBLISH — kirim data sensor ke broker
// =====================================================
void TaskPublish(void *parameter) {

  for (;;) {

    if (mqttClient.connected()) {

      int hujan, ldr, atap, mode;

      if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
        hujan = g_statusHujan;
        ldr   = g_nilaiLDR;
        atap  = g_statusAtap;
        mode  = g_mode;
        xSemaphoreGive(mutexData);
      }

      // Buat JSON manual
      String json = "{";
      json += "\"hujan\":"  + String(hujan) + ",";
      json += "\"ldr\":"    + String(ldr)   + ",";
      json += "\"atap\":"   + String(atap)  + ",";
      json += "\"mode\":"   + String(mode);
      json += "}";

      mqttClient.publish(topicStatus, json.c_str());
      Serial.println("[MQTT] Publish: " + json);
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS); // publish tiap 2 detik
  }
}

// =====================================================
// TASK SENSOR HUJAN
// =====================================================
void TaskBacaRaindrop(void *parameter) {

  pinMode(pinRainDO, INPUT);

  for (;;) {
    int nilai = digitalRead(pinRainDO);

    if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
      g_statusHujan = nilai;
      xSemaphoreGive(mutexData);
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

// =====================================================
// TASK LDR
// =====================================================
void TaskBacaLDR(void *parameter) {

  for (;;) {
    int nilai = analogRead(pinLDRAo);

    if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
      g_nilaiLDR = nilai;
      xSemaphoreGive(mutexData);
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

// =====================================================
// TASK SERVO
// =====================================================
void TaskKontrolServo(void *parameter) {

  int statusAtap             = -1;
  int kondisiStabilSementara = -1;
  unsigned long waktuMulaiStabil = millis();

  for (;;) {

    int hujanLokal, ldrLokal, modeLokal, perintahLokal;

    if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
      hujanLokal    = g_statusHujan;
      ldrLokal      = g_nilaiLDR;
      modeLokal     = g_mode;
      perintahLokal = g_perintahManual;
      xSemaphoreGive(mutexData);
    }

    // ---- MODE MANUAL ----
    if (modeLokal == 1) {

      if (perintahLokal == 0 && statusAtap != 0) {
        Serial.println("[MANUAL] Membuka Atap");
        if (xSemaphoreTake(mutexServo, portMAX_DELAY) == pdTRUE) {
          myservo.write(posisiBuka);
          xSemaphoreGive(mutexServo);
        }
        statusAtap = 0;
        if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
          g_statusAtap     = 0;
          g_perintahManual = -1;
          xSemaphoreGive(mutexData);
        }
      }

      else if (perintahLokal == 1 && statusAtap != 1) {
        Serial.println("[MANUAL] Menutup Atap");
        if (xSemaphoreTake(mutexServo, portMAX_DELAY) == pdTRUE) {
          myservo.write(posisiTutup);
          xSemaphoreGive(mutexServo);
        }
        statusAtap = 1;
        if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
          g_statusAtap     = 1;
          g_perintahManual = -1;
          xSemaphoreGive(mutexData);
        }
      }
    }

    // ---- MODE AUTO ----
    else {

      int kondisiSekarang;
      if (hujanLokal == 0)              kondisiSekarang = 1;
      else if (ldrLokal > batasMendung) kondisiSekarang = 2;
      else                              kondisiSekarang = 0;

      if (kondisiSekarang != kondisiStabilSementara) {
        kondisiStabilSementara = kondisiSekarang;
        waktuMulaiStabil = millis();
      }

      if (millis() - waktuMulaiStabil >= durasiKonfirmasi) {

        if (kondisiStabilSementara == 0 && statusAtap != 0) {
          Serial.println("[AUTO] Cerah -> Membuka Atap");
          if (xSemaphoreTake(mutexServo, portMAX_DELAY) == pdTRUE) {
            myservo.write(posisiBuka);
            xSemaphoreGive(mutexServo);
          }
          statusAtap = 0;
          if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
            g_statusAtap = 0;
            xSemaphoreGive(mutexData);
          }
        }

        else if ((kondisiStabilSementara == 1 || kondisiStabilSementara == 2) && statusAtap != 1) {
          if (kondisiStabilSementara == 1) Serial.println("[AUTO] Hujan -> Menutup Atap");
          else                             Serial.println("[AUTO] Mendung -> Menutup Atap");
          if (xSemaphoreTake(mutexServo, portMAX_DELAY) == pdTRUE) {
            myservo.write(posisiTutup);
            xSemaphoreGive(mutexServo);
          }
          statusAtap = 1;
          if (xSemaphoreTake(mutexData, portMAX_DELAY) == pdTRUE) {
            g_statusAtap = 1;
            xSemaphoreGive(mutexData);
          }
        }
      }
    }

    Serial.print("Mode: "); Serial.print(modeLokal == 0 ? "AUTO" : "MANUAL");
    Serial.print(" | Hujan: "); Serial.print(hujanLokal);
    Serial.print(" | LDR: "); Serial.print(ldrLokal);
    Serial.print(" | Atap: "); Serial.println(statusAtap == 1 ? "TUTUP" : "BUKA");

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

// =====================================================
// SETUP
// =====================================================
void setup() {

  Serial.begin(115200);

  mutexData = xSemaphoreCreateMutex();
  if (mutexData == NULL) { Serial.println("ERROR: mutexData!"); while(true); }

  mutexServo = xSemaphoreCreateMutex();
  if (mutexServo == NULL) { Serial.println("ERROR: mutexServo!"); while(true); }

  ESP32PWM::allocateTimer(0);
  myservo.setPeriodHertz(50);
  myservo.attach(pinServo, 500, 2400);

  if (xSemaphoreTake(mutexServo, portMAX_DELAY) == pdTRUE) {
    myservo.write(posisiBuka);
    xSemaphoreGive(mutexServo);
  }

  // WiFi connect dulu sebelum task jalan
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  xTaskCreatePinnedToCore(TaskWiFi,         "TaskWiFi",    4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskMQTT,         "TaskMQTT",    8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskPublish,      "TaskPublish", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskBacaRaindrop, "TaskRaindrop",2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskBacaLDR,      "TaskLDR",     2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(TaskKontrolServo, "TaskServo",   4096, NULL, 2, NULL, 0);

  Serial.println("==================================");
  Serial.println("Sistem RTOS Atap Jemuran Mulai...");
  Serial.println("==================================");
}

// =====================================================
// LOOP
// =====================================================
void loop() {
  vTaskDelete(NULL);
}