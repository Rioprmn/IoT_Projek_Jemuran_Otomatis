# 🏠 Atap Jemuran Otomatis — ESP32 + FreeRTOS + MQTT

Sistem embedded berbasis **ESP32** untuk membuka/menutup atap jemuran secara otomatis berdasarkan kondisi cuaca (hujan & mendung), dilengkapi kontrol manual dan monitoring real-time melalui **web dashboard** via protokol **MQTT**.

Project ini dibuat sebagai Tugas Akhir (UAS) mata kuliah Embedded System.

![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-green)
![Protocol](https://img.shields.io/badge/Protocol-MQTT-orange)
![Broker](https://img.shields.io/badge/Broker-HiveMQ%20Cloud-red)

---

## ✨ Fitur

- 🌧️ Deteksi hujan otomatis (sensor raindrop)
- ☁️ Deteksi cuaca mendung/cerah (sensor LDR)
- 🔄 Kontrol servo otomatis untuk membuka/menutup atap
- 🎛️ Mode **AUTO** dan **MANUAL**
- 🖱️ Kontrol manual jarak jauh dari web (tombol BUKA/TUTUP)
- 📊 Dashboard web real-time (status sensor, kondisi cuaca, status atap)
- 📡 Komunikasi dua arah via **MQTT** (publish/subscribe) menggunakan broker **HiveMQ Cloud**
- ⚙️ Arsitektur **FreeRTOS multi-task**, dipisah per-core (dual-core pinning)
- 🔒 Shared variable diproteksi dengan **mutex** (anti race condition)
- 🔁 Auto-reconnect WiFi & MQTT saat koneksi putus
- ⏱️ Debounce logic (1.5 detik) untuk mencegah servo "flip-flop"

---

## 🏗️ Arsitektur Sistem

Menggunakan pendekatan **decoupled architecture** — firmware ESP32 dan web dashboard terpisah, dijembatani oleh broker MQTT:

```
┌─────────────────┐        MQTT (TLS, port 8883)        ┌──────────────────┐
│      ESP32       │ ───────────────────────────────────▶ │                  │
│  (Sensor+Servo)  │   publish → atap/status (JSON)       │   HiveMQ Cloud   │
│                  │ ◀─────────────────────────────────── │   (Broker MQTT)  │
│                  │   subscribe ← atap/kontrol            │                  │
│                  │   subscribe ← atap/mode               │                  │
└─────────────────┘                                       └──────────────────┘
                                                                    ▲
                                                                    │ MQTT over WSS (port 8884)
                                                                    ▼
                                                           ┌──────────────────┐
                                                           │  Web Dashboard   │
                                                           │  (HTML/CSS/JS)   │
                                                           └──────────────────┘
```

Keuntungan arsitektur ini:
- Tidak ada masalah CORS (komunikasi lewat broker, bukan langsung HTTP)
- Web dashboard bisa di-hosting di mana saja (termasuk GitHub Pages)
- ESP32 dan web client tidak perlu berada di jaringan yang sama

---

## 🔧 Hardware

| Komponen          | Pin ESP32   | Tipe        | Keterangan                          |
|--------------------|------------|-------------|--------------------------------------|
| Servo SG90         | GPIO 13    | PWM         | Penggerak buka/tutup atap            |
| Raindrop Sensor    | GPIO 14    | Digital (DO)| Deteksi hujan (0 = hujan, 1 = kering)|
| LDR (cahaya)       | GPIO 35    | Analog (ADC)| Deteksi kondisi cerah/mendung        |

**Posisi servo:**
- Buka atap → `0°`
- Tutup atap → `180°`

**Threshold mendung:** nilai LDR > `2500`

---

## ⚙️ Software & Library

**Firmware (Arduino IDE):**
- [`ESP32Servo`](https://github.com/madhephaestus/ESP32Servo) — kontrol servo
- [`PubSubClient`](https://github.com/knolleary/pubsubclient) by Nick O'Leary — client MQTT
- `WiFiClientSecure` — koneksi TLS ke broker (bawaan core ESP32)

**Web Dashboard:**
- HTML / CSS / JavaScript murni
- [`MQTT.js`](https://github.com/mqttjs/MQTT.js) (via CDN) — client MQTT di browser (WebSocket)

**Broker MQTT:**
- [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/) (Free Tier)

---

## 📡 MQTT Topics

| Topic            | Arah                          | Payload                          | Keterangan                  |
|-------------------|-------------------------------|-----------------------------------|------------------------------|
| `atap/status`     | ESP32 → Broker → Web          | JSON `{hujan, ldr, atap, mode}`   | Dipublish tiap 2 detik       |
| `atap/kontrol`    | Web → Broker → ESP32          | `"BUKA"` / `"TUTUP"`             | Hanya aktif saat mode MANUAL |
| `atap/mode`       | Web → Broker → ESP32          | `"AUTO"` / `"MANUAL"`           | Switch mode operasi          |

**Contoh payload `atap/status`:**
```json
{"hujan":1,"ldr":2388,"atap":0,"mode":0}
```
> `hujan`: 1 = kering, 0 = hujan · `atap`: 0 = buka, 1 = tutup · `mode`: 0 = AUTO, 1 = MANUAL

---

## 🧠 Logika Sistem

**Mode AUTO:**
1. Jika sensor mendeteksi hujan → atap **TUTUP**
2. Jika tidak hujan tapi LDR > 2500 (mendung) → atap **TUTUP**
3. Jika cerah → atap **BUKA**
4. Perubahan kondisi harus stabil selama **1.5 detik** sebelum servo bergerak (debounce), untuk menghindari servo bergerak berulang akibat noise sensor.

**Mode MANUAL:**
- Servo bergerak langsung sesuai perintah dari dashboard web (tombol BUKA/TUTUP), mengabaikan kondisi sensor.

---

## 🧵 Task FreeRTOS

| Task                 | Fungsi                                   | Core |
|----------------------|-------------------------------------------|------|
| `TaskWiFi`           | Maintain & auto-reconnect koneksi WiFi    | 0    |
| `TaskMQTT`           | Maintain koneksi & loop MQTT client       | 0    |
| `TaskPublish`        | Publish data sensor ke broker (tiap 2s)   | 0    |
| `TaskBacaRaindrop`   | Baca sensor hujan                         | 1    |
| `TaskBacaLDR`        | Baca sensor cahaya (LDR)                  | 1    |
| `TaskKontrolServo`   | Logika AUTO/MANUAL & kontrol servo        | 0    |

Variabel yang dipakai bersama antar task (`g_statusHujan`, `g_nilaiLDR`, `g_statusAtap`, `g_mode`, dll) diproteksi menggunakan **mutex** (`mutexData`, `mutexServo`) untuk mencegah race condition.

---

## 🚀 Cara Menjalankan

### 1. Setup Broker MQTT (HiveMQ Cloud)
1. Daftar di [hivemq.com/mqtt-cloud-broker](https://www.hivemq.com/mqtt-cloud-broker/)
2. Buat cluster **Free**, tunggu sampai status `Running`
3. Buat credentials di tab **Access Management** (permission: *Publish and Subscribe*)
4. Catat: Cluster URL, Port `8883` (ESP32) & `8884` (Web), Username, Password

### 2. Firmware ESP32
1. Buka file `.ino` di Arduino IDE
2. Install library: `ESP32Servo`, `PubSubClient`
3. Sesuaikan konfigurasi di bagian atas kode:
   ```cpp
   const char* ssid     = "NAMA_WIFI";
   const char* password = "PASSWORD_WIFI";

   const char* mqttServer   = "xxxx.s1.eu.hivemq.cloud";
   const char* mqttUser     = "username_hivemq";
   const char* mqttPassword = "password_hivemq";
   ```
4. Upload ke board ESP32
5. Buka Serial Monitor (baud `115200`) untuk verifikasi:
   ```
   IP Address : 192.168.x.x
   [MQTT] Connected!
   [MQTT] Subscribed ke atap/kontrol & atap/mode
   [MQTT] Publish: {"hujan":1,"ldr":2388,"atap":0,"mode":0}
   ```

### 3. Web Dashboard
1. Sesuaikan kredensial broker di `index.html`:
   ```js
   const broker = "wss://xxxx.s1.eu.hivemq.cloud:8884/mqtt";
   ```
2. Buka file dengan **Live Server** (ekstensi VS Code) atau langsung double-click di file explorer
3. Dashboard otomatis terhubung ke broker dan menampilkan data sensor secara real-time

---

## 📂 Struktur Project

```
atap-jemuran-otomatis/
├── firmware/
│   └── atap_jemuran.ino     # Kode ESP32 (FreeRTOS + MQTT)
├── web/
│   └── index.html            # Dashboard monitoring & kontrol
└── README.md
```

---

## ✅ Status Pengujian

| Fitur                          | Status |
|--------------------------------|--------|
| Servo berjalan                 | ✅     |
| Sensor hujan                   | ✅     |
| Sensor LDR                     | ✅     |
| FreeRTOS multi-task            | ✅     |
| WiFi + auto-reconnect          | ✅     |
| MQTT publish/subscribe         | ✅     |
| Web interface monitoring       | ✅     |
| Mode AUTO/MANUAL               | ✅     |
| Kontrol manual dari web        | ✅     |

---

## ⚠️ Catatan & Troubleshooting

- ESP32 hanya mendukung WiFi **2.4GHz**, pastikan tidak terhubung ke jaringan 5GHz.
- Jika `[MQTT]` tidak muncul di Serial Monitor setelah WiFi connect, kemungkinan TLS handshake lambat — tambahkan `espClient.setTimeout(15)` sebelum koneksi MQTT.
- Pastikan port broker yang digunakan benar: `8883` untuk firmware (TLS), `8884` untuk web (WSS).

---

## 👤 Penulis

**Rio Permana**
Tugas UAS — Embedded System

## 📄 Lisensi

Project ini dibuat untuk keperluan akademik dan dapat digunakan secara bebas untuk tujuan pembelajaran.
