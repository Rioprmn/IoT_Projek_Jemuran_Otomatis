<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Atap Jemuran Otomatis — README</title>
  <link href="https://fonts.googleapis.com/css2?family=Space+Grotesk:wght@300;400;500;600;700&family=JetBrains+Mono:wght@400;500&display=swap" rel="stylesheet">
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    :root {
      --bg:        #080d14;
      --surface:   #0e1622;
      --border:    #1a2740;
      --sky:       #38bdf8;
      --rain:      #60a5fa;
      --sun:       #fbbf24;
      --green:     #34d399;
      --muted:     #4a6080;
      --text:      #c8d8ec;
      --heading:   #e8f2ff;
    }

    html { scroll-behavior: smooth; }

    body {
      font-family: 'Space Grotesk', sans-serif;
      background: var(--bg);
      color: var(--text);
      line-height: 1.7;
      overflow-x: hidden;
    }

    /* ── HERO ── */
    .hero {
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      text-align: center;
      padding: 60px 24px;
      position: relative;
      overflow: hidden;
    }

    .hero::before {
      content: '';
      position: absolute;
      inset: 0;
      background:
        radial-gradient(ellipse 80% 60% at 50% 0%, rgba(56,189,248,0.08) 0%, transparent 70%),
        radial-gradient(ellipse 50% 40% at 80% 80%, rgba(96,165,250,0.06) 0%, transparent 60%);
      pointer-events: none;
    }

    .hero-badge {
      display: inline-flex;
      align-items: center;
      gap: 8px;
      background: rgba(56,189,248,0.08);
      border: 1px solid rgba(56,189,248,0.2);
      border-radius: 999px;
      padding: 6px 16px;
      font-size: 0.75rem;
      font-family: 'JetBrains Mono', monospace;
      color: var(--sky);
      letter-spacing: 0.05em;
      margin-bottom: 32px;
    }

    .hero-badge .dot {
      width: 6px; height: 6px;
      border-radius: 50%;
      background: var(--green);
      box-shadow: 0 0 8px var(--green);
      animation: pulse 2s ease-in-out infinite;
    }

    @keyframes pulse {
      0%, 100% { opacity: 1; transform: scale(1); }
      50% { opacity: 0.5; transform: scale(0.8); }
    }

    .hero-icon {
      font-size: 5rem;
      margin-bottom: 24px;
      display: block;
      filter: drop-shadow(0 0 32px rgba(56,189,248,0.3));
      animation: float 4s ease-in-out infinite;
    }

    @keyframes float {
      0%, 100% { transform: translateY(0); }
      50% { transform: translateY(-12px); }
    }

    h1 {
      font-size: clamp(2.2rem, 6vw, 4rem);
      font-weight: 700;
      color: var(--heading);
      line-height: 1.15;
      letter-spacing: -0.02em;
      margin-bottom: 16px;
    }

    h1 span {
      background: linear-gradient(135deg, var(--sky), var(--rain));
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      background-clip: text;
    }

    .hero-sub {
      font-size: 1.1rem;
      color: var(--muted);
      max-width: 560px;
      margin-bottom: 48px;
    }

    .badge-row {
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      justify-content: center;
      margin-bottom: 48px;
    }

    .badge {
      display: inline-flex;
      align-items: center;
      gap: 6px;
      padding: 5px 14px;
      border-radius: 8px;
      font-size: 0.78rem;
      font-family: 'JetBrains Mono', monospace;
      font-weight: 500;
      border: 1px solid;
    }

    .badge-blue  { background: rgba(56,189,248,0.08); border-color: rgba(56,189,248,0.25); color: var(--sky); }
    .badge-green { background: rgba(52,211,153,0.08); border-color: rgba(52,211,153,0.25); color: var(--green); }
    .badge-gold  { background: rgba(251,191,36,0.08); border-color: rgba(251,191,36,0.25); color: var(--sun); }

    .hero-cta {
      display: inline-flex;
      align-items: center;
      gap: 10px;
      background: linear-gradient(135deg, var(--sky), var(--rain));
      color: #000;
      font-weight: 700;
      font-size: 0.9rem;
      padding: 14px 32px;
      border-radius: 12px;
      text-decoration: none;
      transition: opacity 0.2s, transform 0.2s;
    }

    .hero-cta:hover { opacity: 0.88; transform: translateY(-2px); }

    /* ── SECTION SHARED ── */
    section {
      padding: 80px 24px;
      max-width: 900px;
      margin: 0 auto;
    }

    .section-label {
      font-family: 'JetBrains Mono', monospace;
      font-size: 0.72rem;
      color: var(--sky);
      letter-spacing: 0.12em;
      text-transform: uppercase;
      margin-bottom: 12px;
    }

    h2 {
      font-size: clamp(1.5rem, 4vw, 2.2rem);
      font-weight: 700;
      color: var(--heading);
      letter-spacing: -0.02em;
      margin-bottom: 32px;
      line-height: 1.2;
    }

    /* ── DIVIDER ── */
    .divider {
      height: 1px;
      background: linear-gradient(90deg, transparent, var(--border), transparent);
      margin: 0 24px;
    }

    /* ── ABOUT ── */
    .about-grid {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 16px;
    }

    @media (max-width: 600px) { .about-grid { grid-template-columns: 1fr; } }

    .about-card {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 16px;
      padding: 28px;
    }

    .about-card .icon { font-size: 2rem; margin-bottom: 14px; display: block; }
    .about-card h3 { font-size: 1rem; color: var(--heading); font-weight: 600; margin-bottom: 8px; }
    .about-card p { font-size: 0.875rem; color: var(--muted); line-height: 1.6; }

    /* ── ARSITEKTUR ── */
    .arch-box {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 16px;
      padding: 32px;
      margin-bottom: 32px;
      overflow-x: auto;
    }

    pre {
      font-family: 'JetBrains Mono', monospace;
      font-size: 0.82rem;
      color: var(--text);
      line-height: 1.8;
      white-space: pre;
    }

    pre .c-sky   { color: var(--sky); }
    pre .c-green { color: var(--green); }
    pre .c-gold  { color: var(--sun); }
    pre .c-rain  { color: var(--rain); }
    pre .c-muted { color: var(--muted); }

    /* ── FITUR ── */
    .feature-list {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(260px, 1fr));
      gap: 16px;
    }

    .feature-item {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 14px;
      padding: 24px;
      display: flex;
      gap: 16px;
      align-items: flex-start;
      transition: border-color 0.2s, transform 0.2s;
    }

    .feature-item:hover {
      border-color: rgba(56,189,248,0.3);
      transform: translateY(-2px);
    }

    .feature-item .fi-icon {
      font-size: 1.5rem;
      flex-shrink: 0;
      margin-top: 2px;
    }

    .feature-item h4 { font-size: 0.92rem; color: var(--heading); font-weight: 600; margin-bottom: 4px; }
    .feature-item p  { font-size: 0.8rem; color: var(--muted); line-height: 1.5; }

    /* ── HARDWARE ── */
    .hw-table {
      width: 100%;
      border-collapse: collapse;
      font-size: 0.875rem;
    }

    .hw-table th {
      text-align: left;
      padding: 12px 16px;
      color: var(--sky);
      font-family: 'JetBrains Mono', monospace;
      font-size: 0.72rem;
      letter-spacing: 0.08em;
      text-transform: uppercase;
      border-bottom: 1px solid var(--border);
    }

    .hw-table td {
      padding: 14px 16px;
      border-bottom: 1px solid rgba(26,39,64,0.5);
      color: var(--text);
      vertical-align: middle;
    }

    .hw-table tr:last-child td { border-bottom: none; }
    .hw-table tr:hover td { background: rgba(56,189,248,0.03); }

    .pin-badge {
      font-family: 'JetBrains Mono', monospace;
      font-size: 0.75rem;
      background: rgba(56,189,248,0.1);
      color: var(--sky);
      padding: 2px 10px;
      border-radius: 6px;
    }

    .hw-wrap {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 16px;
      overflow: hidden;
    }

    /* ── TOPIC MQTT ── */
    .topic-grid {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 16px;
    }

    @media (max-width: 600px) { .topic-grid { grid-template-columns: 1fr; } }

    .topic-card {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 14px;
      padding: 24px;
    }

    .topic-card .tc-label {
      font-size: 0.7rem;
      font-family: 'JetBrains Mono', monospace;
      letter-spacing: 0.1em;
      text-transform: uppercase;
      margin-bottom: 10px;
    }

    .topic-card .tc-label.pub { color: var(--green); }
    .topic-card .tc-label.sub { color: var(--rain); }

    .topic-tag {
      display: inline-block;
      font-family: 'JetBrains Mono', monospace;
      font-size: 0.82rem;
      padding: 6px 14px;
      border-radius: 8px;
      margin-bottom: 8px;
    }

    .tag-green { background: rgba(52,211,153,0.1); color: var(--green); }
    .tag-blue  { background: rgba(96,165,250,0.1); color: var(--rain); }

    .topic-desc { font-size: 0.8rem; color: var(--muted); margin-top: 4px; }

    /* ── INSTALL ── */
    .step-list { display: flex; flex-direction: column; gap: 20px; }

    .step {
      display: grid;
      grid-template-columns: 48px 1fr;
      gap: 20px;
      align-items: flex-start;
    }

    .step-num {
      width: 48px; height: 48px;
      border-radius: 12px;
      background: rgba(56,189,248,0.1);
      border: 1px solid rgba(56,189,248,0.2);
      display: flex;
      align-items: center;
      justify-content: center;
      font-family: 'JetBrains Mono', monospace;
      font-size: 1rem;
      font-weight: 700;
      color: var(--sky);
      flex-shrink: 0;
    }

    .step-body h4 { font-size: 0.95rem; color: var(--heading); font-weight: 600; margin-bottom: 6px; }
    .step-body p  { font-size: 0.85rem; color: var(--muted); }

    code {
      font-family: 'JetBrains Mono', monospace;
      font-size: 0.82rem;
      background: rgba(56,189,248,0.08);
      color: var(--sky);
      padding: 2px 8px;
      border-radius: 5px;
    }

    .code-block {
      background: #060b11;
      border: 1px solid var(--border);
      border-radius: 12px;
      padding: 20px 24px;
      margin-top: 12px;
      overflow-x: auto;
    }

    .code-block pre { font-size: 0.8rem; }

    /* ── TEAM ── */
    .team-card {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 16px;
      padding: 32px;
      display: flex;
      align-items: center;
      gap: 24px;
    }

    .team-avatar {
      width: 64px; height: 64px;
      border-radius: 14px;
      background: linear-gradient(135deg, var(--sky), var(--rain));
      display: flex;
      align-items: center;
      justify-content: center;
      font-size: 1.8rem;
      flex-shrink: 0;
    }

    .team-info h3 { font-size: 1.05rem; color: var(--heading); font-weight: 600; margin-bottom: 4px; }
    .team-info p  { font-size: 0.83rem; color: var(--muted); }

    /* ── FOOTER ── */
    footer {
      text-align: center;
      padding: 48px 24px;
      border-top: 1px solid var(--border);
      font-size: 0.8rem;
      color: var(--muted);
    }

    footer a { color: var(--sky); text-decoration: none; }
    footer a:hover { text-decoration: underline; }

    /* ── FLOW DIAGRAM ── */
    .flow {
      display: flex;
      align-items: center;
      gap: 0;
      flex-wrap: wrap;
      justify-content: center;
      margin: 32px 0;
    }

    .flow-node {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: 12px;
      padding: 16px 20px;
      text-align: center;
      min-width: 120px;
    }

    .flow-node .fn-icon { font-size: 1.5rem; display: block; margin-bottom: 6px; }
    .flow-node .fn-label { font-size: 0.75rem; color: var(--text); font-weight: 500; }
    .flow-node .fn-sub   { font-size: 0.68rem; color: var(--muted); margin-top: 2px; }

    .flow-arrow {
      color: var(--muted);
      font-size: 1.2rem;
      padding: 0 8px;
    }

    @media (max-width: 600px) {
      .flow { flex-direction: column; }
      .flow-arrow { transform: rotate(90deg); }
      .team-card { flex-direction: column; text-align: center; }
    }
  </style>
</head>
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
