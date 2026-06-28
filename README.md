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
