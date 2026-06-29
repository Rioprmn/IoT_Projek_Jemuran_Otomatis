<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Atap Jemuran Otomatis — README</title>
  <link href="https://fonts.googleapis.com/css2?family=Space+Grotesk:wght@300;400;500;600;700&family=JetBrains+Mono:wght@400;500&display=swap" rel="stylesheet">
  <body>

<!-- ═══════════════ HERO ═══════════════ -->
<div class="hero">
  <div class="hero-badge">
    <span class="dot"></span>
    ESP32 · FreeRTOS · MQTT · IoT
  </div>
  <span class="hero-icon">🏠</span>
  <h1>Atap Jemuran<br><span>Otomatis</span></h1>
  <p class="hero-sub">
    Sistem cerdas berbasis ESP32 yang menutup dan membuka atap jemuran secara otomatis berdasarkan kondisi cuaca — dimonitor dan dikontrol dari mana saja via web.
  </p>

  <div class="badge-row">
    <span class="badge badge-blue">⚙️ ESP32 Dev Module</span>
    <span class="badge badge-gold">🔁 FreeRTOS</span>
    <span class="badge badge-green">📡 MQTT HiveMQ</span>
    <span class="badge badge-blue">🌐 Web Dashboard</span>
    <span class="badge badge-gold">🌧️ Rain Sensor</span>
    <span class="badge badge-green">☀️ LDR Sensor</span>
  </div>

  <a href="#about" class="hero-cta">
    Lihat Dokumentasi ↓
  </a>
</div>

<div class="divider"></div>

<!-- ═══════════════ ABOUT ═══════════════ -->
<section id="about">
  <div class="section-label">// tentang proyek</div>
  <h2>Apa itu Atap Jemuran Otomatis?</h2>

  <div class="about-grid">
    <div class="about-card">
      <span class="icon">🌧️</span>
      <h3>Deteksi Cuaca Real-time</h3>
      <p>Sensor raindrop mendeteksi hujan dan sensor LDR memantau intensitas cahaya untuk menentukan kondisi cerah, mendung, atau hujan.</p>
    </div>
    <div class="about-card">
      <span class="icon">⚡</span>
      <h3>Multi-task dengan FreeRTOS</h3>
      <p>Enam task berjalan paralel: WiFi, MQTT, Publish, Raindrop, LDR, dan Servo — semuanya sinkron via mutex semaphore.</p>
    </div>
    <div class="about-card">
      <span class="icon">📡</span>
      <h3>Monitoring via MQTT</h3>
      <p>Data sensor dipublish ke HiveMQ Cloud setiap 2 detik. Web dashboard subscribe dan menampilkan data secara realtime.</p>
    </div>
    <div class="about-card">
      <span class="icon">🕹️</span>
      <h3>Mode AUTO & MANUAL</h3>
      <p>Pengguna bisa memilih mode otomatis (dikontrol sensor) atau manual (dikontrol dari web dashboard kapan saja).</p>
    </div>
  </div>
</section>

<div class="divider"></div>

<!-- ═══════════════ ARSITEKTUR ═══════════════ -->
<section id="arsitektur">
  <div class="section-label">// arsitektur sistem</div>
  <h2>Bagaimana Sistem Bekerja</h2>

  <div class="flow">
    <div class="flow-node">
      <span class="fn-icon">🌧️☀️</span>
      <div class="fn-label">Sensor</div>
      <div class="fn-sub">Rain + LDR</div>
    </div>
    <span class="flow-arrow">→</span>
    <div class="flow-node">
      <span class="fn-icon">🔲</span>
      <div class="fn-label">ESP32</div>
      <div class="fn-sub">FreeRTOS</div>
    </div>
    <span class="flow-arrow">→</span>
    <div class="flow-node">
      <span class="fn-icon">📡</span>
      <div class="fn-label">HiveMQ</div>
      <div class="fn-sub">MQTT Broker</div>
    </div>
    <span class="flow-arrow">→</span>
    <div class="flow-node">
      <span class="fn-icon">🌐</span>
      <div class="fn-label">Dashboard</div>
      <div class="fn-sub">Web Browser</div>
    </div>
  </div>

  <div class="arch-box">
<pre>
<span class="c-sky">ESP32 — FreeRTOS Tasks</span>
<span class="c-muted">─────────────────────────────────────────────────────</span>
  <span class="c-green">TaskWiFi</span>       <span class="c-muted">→</span> Jaga koneksi WiFi, auto-reconnect         <span class="c-muted">[Core 0]</span>
  <span class="c-green">TaskMQTT</span>       <span class="c-muted">→</span> Connect & maintain broker HiveMQ TLS      <span class="c-muted">[Core 0]</span>
  <span class="c-green">TaskPublish</span>    <span class="c-muted">→</span> Publish JSON sensor tiap 2 detik          <span class="c-muted">[Core 0]</span>
  <span class="c-green">TaskBacaRain</span>   <span class="c-muted">→</span> Baca digital pin raindrop sensor          <span class="c-muted">[Core 1]</span>
  <span class="c-green">TaskBacaLDR</span>    <span class="c-muted">→</span> Baca analog pin LDR sensor                <span class="c-muted">[Core 1]</span>
  <span class="c-gold">TaskServo</span>      <span class="c-muted">→</span> Kontrol servo (AUTO/MANUAL + debounce)    <span class="c-muted">[Core 0]</span>

<span class="c-sky">MQTT Topics</span>
<span class="c-muted">─────────────────────────────────────────────────────</span>
  <span class="c-green">PUBLISH</span>  <span class="c-rain">atap/status</span>   <span class="c-muted">→</span> {"hujan":1,"ldr":1200,"atap":0,"mode":0}
  <span class="c-green">SUBSCRIBE</span> <span class="c-rain">atap/kontrol</span>  <span class="c-muted">←</span> "BUKA" | "TUTUP"
  <span class="c-green">SUBSCRIBE</span> <span class="c-rain">atap/mode</span>     <span class="c-muted">←</span> "AUTO" | "MANUAL"
</pre>
  </div>
</section>

<div class="divider"></div>

<!-- ═══════════════ FITUR ═══════════════ -->
<section id="fitur">
  <div class="section-label">// fitur utama</div>
  <h2>Apa Saja yang Bisa Dilakukan</h2>

  <div class="feature-list">
    <div class="feature-item">
      <span class="fi-icon">🔁</span>
      <div>
        <h4>FreeRTOS Multi-task</h4>
        <p>6 task paralel dengan mutex semaphore untuk proteksi shared data dan akses servo.</p>
      </div>
    </div>
    <div class="feature-item">
      <span class="fi-icon">📶</span>
      <div>
        <h4>WiFi Multi-network</h4>
        <p>Daftarkan beberapa jaringan WiFi, ESP32 otomatis pilih yang tersedia dan auto-reconnect.</p>
      </div>
    </div>
    <div class="feature-item">
      <span class="fi-icon">🌧️</span>
      <div>
        <h4>Deteksi Preventif</h4>
        <p>Atap ditutup saat mendung (LDR > threshold) sebelum hujan turun — bukan hanya saat hujan.</p>
      </div>
    </div>
    <div class="feature-item">
      <span class="fi-icon">⏱️</span>
      <div>
        <h4>Debounce Konfirmasi</h4>
        <p>Kondisi harus stabil 1.5 detik sebelum servo bergerak — mencegah servo goyang akibat noise sensor.</p>
      </div>
    </div>
    <div class="feature-item">
      <span class="fi-icon">🕹️</span>
      <div>
        <h4>Kontrol Manual</h4>
        <p>Override sensor kapan saja via web dashboard. Tombol BUKA/TUTUP aktif hanya saat mode MANUAL.</p>
      </div>
    </div>
    <div class="feature-item">
      <span class="fi-icon">🔒</span>
      <div>
        <h4>TLS Encrypted MQTT</h4>
        <p>Koneksi ke HiveMQ Cloud menggunakan port 8883 dengan enkripsi TLS — data aman di jaringan publik.</p>
      </div>
    </div>
  </div>
</section>

<div class="divider"></div>

<!-- ═══════════════ HARDWARE ═══════════════ -->
<section id="hardware">
  <div class="section-label">// hardware</div>
  <h2>Komponen yang Digunakan</h2>

  <div class="hw-wrap">
    <table class="hw-table">
      <thead>
        <tr>
          <th>Komponen</th>
          <th>Fungsi</th>
          <th>Pin ESP32</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>ESP32 Dev Module</td>
          <td>Mikrokontroler utama + WiFi</td>
          <td>—</td>
        </tr>
        <tr>
          <td>Servo Motor</td>
          <td>Aktuator buka/tutup atap</td>
          <td><span class="pin-badge">GPIO 13</span></td>
        </tr>
        <tr>
          <td>Rain Sensor (DO)</td>
          <td>Deteksi hujan (digital)</td>
          <td><span class="pin-badge">GPIO 14</span></td>
        </tr>
        <tr>
          <td>LDR Sensor (AO)</td>
          <td>Deteksi intensitas cahaya (analog)</td>
          <td><span class="pin-badge">GPIO 35</span></td>
        </tr>
      </tbody>
    </table>
  </div>
</section>

<div class="divider"></div>

<!-- ═══════════════ MQTT TOPICS ═══════════════ -->
<section id="mqtt">
  <div class="section-label">// mqtt topics</div>
  <h2>Topik MQTT</h2>

  <div class="topic-grid">
    <div class="topic-card">
      <div class="tc-label pub">↑ PUBLISH</div>
      <div class="topic-tag tag-green">atap/status</div>
      <p class="topic-desc">ESP32 publish data sensor setiap 2 detik</p>
      <div class="code-block" style="margin-top:14px;">
<pre style="font-size:0.75rem;">{
  "hujan": 1,
  "ldr": 1200,
  "atap": 0,
  "mode": 0
}</pre>
      </div>
    </div>
    <div class="topic-card">
      <div class="tc-label sub">↓ SUBSCRIBE</div>
      <div style="display:flex;flex-direction:column;gap:8px;margin-bottom:12px;">
        <div>
          <div class="topic-tag tag-blue">atap/kontrol</div>
          <p class="topic-desc">Terima perintah: <code>BUKA</code> atau <code>TUTUP</code></p>
        </div>
        <div>
          <div class="topic-tag tag-blue">atap/mode</div>
          <p class="topic-desc">Terima mode: <code>AUTO</code> atau <code>MANUAL</code></p>
        </div>
      </div>
    </div>
  </div>
</section>

<div class="divider"></div>

<!-- ═══════════════ INSTALASI ═══════════════ -->
<section id="instalasi">
  <div class="section-label">// instalasi</div>
  <h2>Cara Menjalankan Proyek</h2>

  <div class="step-list">
    <div class="step">
      <div class="step-num">01</div>
      <div class="step-body">
        <h4>Clone Repository</h4>
        <div class="code-block">
          <pre><span style="color:var(--green)">$</span> git clone https://github.com/username/atap-jemuran.git</pre>
        </div>
      </div>
    </div>

    <div class="step">
      <div class="step-num">02</div>
      <div class="step-body">
        <h4>Install Library Arduino IDE</h4>
        <p>Buka <code>Library Manager</code> dan install library berikut:</p>
        <div class="code-block" style="margin-top:10px;">
<pre><span class="c-green">✓</span> ESP32Servo       <span class="c-muted">by Kevin Harrington</span>
<span class="c-green">✓</span> PubSubClient     <span class="c-muted">by Nick O'Leary</span>
<span class="c-green">✓</span> WiFiMulti        <span class="c-muted">built-in ESP32</span>
<span class="c-green">✓</span> WiFiClientSecure <span class="c-muted">built-in ESP32</span></pre>
        </div>
      </div>
    </div>

    <div class="step">
      <div class="step-num">03</div>
      <div class="step-body">
        <h4>Konfigurasi WiFi & MQTT</h4>
        <p>Edit bagian konfigurasi di <code>AtapJemuran.ino</code>:</p>
        <div class="code-block" style="margin-top:10px;">
<pre><span class="c-muted">// Tambah jaringan WiFi</span>
wifiMulti.<span class="c-sky">addAP</span>(<span style="color:var(--sun)">"NamaWiFi1"</span>, <span style="color:var(--sun)">"Password1"</span>);
wifiMulti.<span class="c-sky">addAP</span>(<span style="color:var(--sun)">"NamaWiFi2"</span>, <span style="color:var(--sun)">"Password2"</span>);

<span class="c-muted">// Kredensial MQTT HiveMQ</span>
<span class="c-rain">const char*</span> mqttServer   = <span style="color:var(--sun)">"xxxx.hivemq.cloud"</span>;
<span class="c-rain">const char*</span> mqttUser     = <span style="color:var(--sun)">"username"</span>;
<span class="c-rain">const char*</span> mqttPassword = <span style="color:var(--sun)">"password"</span>;</pre>
        </div>
      </div>
    </div>

    <div class="step">
      <div class="step-num">04</div>
      <div class="step-body">
        <h4>Upload ke ESP32</h4>
        <p>Pilih board <code>ESP32 Dev Module</code>, pilih port COM yang sesuai, lalu klik Upload. Pantau Serial Monitor di <code>115200 baud</code>.</p>
      </div>
    </div>

    <div class="step">
      <div class="step-num">05</div>
      <div class="step-body">
        <h4>Buka Web Dashboard</h4>
        <p>Buka file <code>index.html</code> di browser. Dashboard otomatis terhubung ke HiveMQ dan menampilkan data sensor secara realtime.</p>
      </div>
    </div>
  </div>
</section>

<div class="divider"></div>

<!-- ═══════════════ TEAM ═══════════════ -->
<section id="team">
  <div class="section-label">// dibuat oleh</div>
  <h2>Tim Pengembang</h2>

  <div class="team-card">
    <div class="team-avatar">👨‍💻</div>
    <div class="team-info">
      <h3>Mahasiswa Teknik — Universitas Teknologi Bandung</h3>
      <p>Proyek Akhir Mata Kuliah Mikrokontroler &amp; IoT — 2026</p>
      <p style="margin-top:8px; font-family:'JetBrains Mono',monospace; font-size:0.75rem; color:var(--sky);">
        ESP32 · FreeRTOS · MQTT · HiveMQ · HTML/CSS/JS
      </p>
    </div>
  </div>
</section>

<!-- ═══════════════ FOOTER ═══════════════ -->
<footer>
  <p style="margin-bottom:8px;">🏠 Atap Jemuran Otomatis — ESP32 IoT Project</p>
  <p>Dibuat dengan ☁️ dan ☀️ · Broker by <a href="https://www.hivemq.com" target="_blank">HiveMQ Cloud</a></p>
</footer>

</body>
</html>
