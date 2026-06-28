Pengenalan Proyek

Atap Jemuran Monitor

Deskripsi

Atap Jemuran Monitor adalah sebuah aplikasi web yang dibuat untuk memantau dan mengendalikan sistem Atap Jemuran Otomatis berbasis ESP32. Website ini berfungsi sebagai dashboard yang menampilkan kondisi alat secara real-time menggunakan protokol komunikasi MQTT.

ESP32 membaca data dari sensor hujan dan sensor cahaya (LDR), kemudian mengirimkan data tersebut ke MQTT Broker (HiveMQ Cloud). Website menerima data tersebut dan langsung menampilkannya tanpa perlu melakukan refresh halaman.

Selain menampilkan informasi, website juga dapat mengirimkan perintah ke ESP32. Pengguna dapat memilih mode AUTO atau MANUAL, serta membuka dan menutup atap secara manual apabila diperlukan. Dengan adanya dashboard ini, pengguna dapat memantau kondisi jemuran dan mengendalikan atap dari mana saja selama perangkat terhubung ke internet.

---

Tampilan Dashboard

Dashboard terdiri dari beberapa bagian yang memiliki fungsi berbeda.

Status Koneksi MQTT

Menampilkan kondisi koneksi antara website dan MQTT Broker.

Sensor Hujan

Menampilkan hasil pembacaan sensor hujan.

Nilai Sensor LDR

Menampilkan nilai sensor cahaya yang dibaca oleh ESP32.

Kondisi Cuaca

Menampilkan hasil pengolahan data sensor menjadi kondisi cuaca.

Status Atap

Menampilkan posisi atap saat ini.

Mode Operasi

Menampilkan mode yang sedang digunakan, yaitu AUTO atau MANUAL.

Tombol Kontrol Manual

Digunakan untuk membuka atau menutup atap ketika sistem berada pada mode MANUAL.

Last Update

Menampilkan waktu terakhir data diterima dari ESP32 sehingga pengguna mengetahui bahwa informasi yang ditampilkan masih terbaru.



Fitur

Website ini memiliki beberapa fitur yang membantu pengguna untuk memantau dan mengendalikan atap jemuran.

Monitoring Data Secara Real-Time
Website menerima data yang dikirim oleh ESP32 menggunakan MQTT. Setiap kali data berubah, tampilan website akan langsung ikut berubah tanpa perlu menekan tombol refresh.

Status Sensor Hujan
Fitur ini menunjukkan apakah sensor mendeteksi hujan atau tidak.

Status yang ditampilkan adalah:
HUJAN
KERING
Dengan melihat status ini, pengguna dapat mengetahui apakah kondisi di luar sedang hujan atau tidak.

Nilai Sensor Cahaya (LDR)
Website menampilkan nilai yang dibaca oleh sensor cahaya (LDR).
Nilai ini digunakan untuk mengetahui apakah kondisi di sekitar jemuran sedang terang atau gelap. Semakin besar nilai LDR, biasanya menunjukkan kondisi yang lebih gelap atau mendung.

Kondisi Cuaca
Website mengolah data dari sensor hujan dan sensor LDR menjadi informasi cuaca yang lebih mudah dipahami.

Kondisi yang ditampilkan meliputi:
Cerah
Mendung
Hujan
Dengan fitur ini, pengguna tidak perlu melihat nilai sensor secara langsung.

Status Atap
Website menampilkan posisi atap jemuran saat ini.

Status yang ditampilkan yaitu:
BUKA
TUTUP
Pengguna dapat mengetahui apakah atap sedang terbuka atau sudah tertutup.

Mode Operasi
Sistem memiliki dua mode kerja.

AUTO
Pada mode AUTO, ESP32 akan mengatur atap secara otomatis berdasarkan data dari sensor hujan dan sensor cahaya.

MANUAL
Pada mode MANUAL, pengguna dapat mengendalikan atap sendiri melalui website.

Kontrol Manual
Saat mode MANUAL aktif, pengguna dapat menggunakan tombol BUKA atau TUTUP.
Setelah tombol ditekan, website akan mengirimkan perintah ke ESP32 melalui MQTT. ESP32 kemudian menggerakkan servo sesuai perintah yang diterima.

Reconnect Otomatis
Jika koneksi website ke MQTT Broker terputus, website akan mencoba menyambungkan kembali secara otomatis. Dengan begitu, pengguna tidak perlu membuka ulang halaman website.

Tampilan Responsif
Website dapat digunakan di berbagai ukuran layar, seperti komputer, laptop, tablet, maupun smartphone. Tampilan akan menyesuaikan ukuran perangkat yang digunakan.

Teknologi yang Digunakan
Proyek ini dibuat menggunakan beberapa teknologi berikut.

HTML5
Digunakan untuk membuat struktur atau kerangka halaman website.

CSS3
Digunakan untuk mengatur warna, tata letak, ukuran, dan tampilan website agar lebih rapi dan menarik.

JavaScript (Vanilla JS)
Digunakan untuk menjalankan logika program, mengolah data, dan menghubungkan website dengan MQTT.

MQTT.js
Library JavaScript yang digunakan agar website dapat mengirim dan menerima data melalui MQTT.

HiveMQ Cloud
Berfungsi sebagai MQTT Broker, yaitu penghubung antara website dan ESP32 agar keduanya dapat saling bertukar data.

ESP32
Mikrokontroler yang membaca data dari sensor, mengirim data ke website, dan mengendalikan servo.

Sensor Hujan
Digunakan untuk mendeteksi apakah sedang turun hujan atau tidak.

Sensor LDR
Digunakan untuk mengukur tingkat cahaya di sekitar jemuran.

Servo Motor
Digunakan untuk membuka dan menutup atap jemuran sesuai perintah dari ESP32.
