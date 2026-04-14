## 1. Jelaskan Proses dari Input Keyboard hingga LED Menyala/Mati

**Proses Tahap Demi Tahap:**
1. **Input dari Keyboard**
   - Pengguna mengetik karakter '1', '0', atau karakter lain di Serial Monitor
   - Karakter dikirim melalui port USB/Serial dengan baud rate 9600 bps

2. **Transmisi Data**
   - Data dikirimkan secara serial (bit per bit) dari komputer ke Arduino
   - Arduino menerima data dan menyimpannya di buffer serial

3. **Pembacaan Data**
   - `Serial.available()` mengecek apakah ada data di buffer
   - Jika ada data (> 0), `Serial.read()` membaca 1 karakter dari buffer
   - Karakter disimpan dalam variabel `data`

4. **Pemrosesan Logika**
   - Jika `data == '1'`: LED dihidupkan (digitalWrite HIGH)
   - Jika `data == '0'`: LED dimatikan (digitalWrite LOW)
   - Jika karakter lain: kirim pesan "Perintah tidak dikenal"

5. **Output Fisik**
   - `digitalWrite(PIN_LED, HIGH)` membuat pin 12 bernilai HIGH (5V)
   - Arus mengalir melalui LED → LED menyala
   - `digitalWrite(PIN_LED, LOW)` membuat pin 12 bernilai LOW (0V)
   - Arus berhenti → LED padam

6. **Feedback ke Komputer**
   - `Serial.println()` mengirimkan status kembali ke Serial Monitor
   - Pengguna melihat respons di layar

---

## 2. Mengapa Digunakan Serial.available() Sebelum Membaca Data?

`Serial.available()` digunakan karena:
1. **Mencegah Pembacaan Data Kosong**
   - Tanpa pengecekan, jika buffer kosong `Serial.read()` mengembalikan -1
   - Karakter yang sesuai adalah ASCII, tetapi -1 bukan karakter valid
   - Dapat menyebabkan perilaku tidak terduga

2. **Efisiensi Program**
   - Menghindari operasi pembacaan yang tidak perlu
   - Program tidak "menunggu" data jika belum ada

3. **Mencegah Bug Logic**
   - Tanpa pengecekan, kondisi if/else bisa error
   - Misalnya: `if (data == '1')` dengan data = -1 akan selalu false

---

## 3. Modifikasi Program untuk LED Berkedip dengan Input '2'

```cpp
const int PIN_LED = 12; //pin led

bool blinkMode = false;  // status apakah LED sedang berkedip
unsigned long previousMillis = 0;  // menyimpan waktu eksekusi terakhir
const unsigned long interval = 500;  // interval waktu 500ms untuk kedip

void setup() {
    Serial.begin(9600);
    Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED, '2' untuk berkedip");
    pinMode(PIN_LED, OUTPUT);
}

void loop() {

  // cek apakah ada input dari serial monitor
  if (Serial.available() > 0) {
    char data = Serial.read();  // baca 1 karakter dari serial
    
    // proses berdasarkan input
    if (data == '1') {
      // nyalakan led dan hentikan blink mode
      blinkMode = false;
      digitalWrite(PIN_LED, HIGH);
      Serial.println("LED ON");
    }
    else if (data == '0') {
      // matikan LED dan hentikan blink mode
      blinkMode = false;
      digitalWrite(PIN_LED, LOW);
      Serial.println("LED OFF");
    }
    else if (data == '2') {
      // aktifkan blink mode
      blinkMode = true;
      previousMillis = millis();  // Reset timer
      Serial.println("LED BLINK - tekan '0' atau '1' untuk menghentikan");
    }
    else if (data != '\n' && data != '\r') {
      // Input tidak valid (bukan 1, 0, 2, atau karakter khusus)
      blinkMode = false;  // Hentikan blink
      digitalWrite(PIN_LED, LOW);  // Matikan LED
      Serial.println("Perintah tidak dikenal - LED OFF");
    }
  }
  
  // blink logic
  if (blinkMode) {
    unsigned long currentMillis = millis();  // ambil waktu sekarang
    
    // cek apakah sudah mencapai interval waktu
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;  // update waktu referensi
      
      // toggle led (jika HIGH jadi LOW, jika LOW jadi HIGH)
      digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    }
  }
}
```

---

## 4. Pilih delay() atau millis() dan Penjelasan Pengaruhnya

Untuk aplikasi yang memerlukan input real-time (seperti UART serial), gunakan `millis()`. Meskipun lebih kompleks, keuntungan responsivitas jauh melampaui kekuruangannya. `delay()` hanya cocok untuk aplikasi sederhana tanpa input real-time.

#### **Menggunakan delay():**
```cpp
if (data == '2') {
    while (blinkMode) {
        digitalWrite(PIN_LED, HIGH);
        delay(500);         // disini program terhenti!
        digitalWrite(PIN_LED, LOW);
        delay(500);         // disini program terhenti!
        // serial input tidak bisa baca selama delay
    }
}
```
**Masalah:**
- Saat `delay()` berjalan, loop tidak dieksekusi
- Input keyboard diabaikan sampai delay selesai
- Tidak bisa mengganti mode berkedip dengan input baru
- Program "freeze" dari perspektif pengguna

#### **Menggunakan millis():**
**Keuntungan:**
- Loop selalu berjalan
- Serial input selalu bisa dibaca
- Program tetap responsif
- Bisa mengganti mode kapan saja
- Hemat CPU resource