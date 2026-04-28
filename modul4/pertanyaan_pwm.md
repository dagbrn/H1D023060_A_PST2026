## 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!

Fungsi analogWrite() dapat mengatur kecerahan LED karena menggunakan teknik Pulse Width Modulation (PWM).

Penjelasan:
- analogWrite() tidak benar-benar mengeluarkan tegangan analog, melainkan mengirimkan sinyal digital dalam bentuk pulsa dengan frekuensi tinggi (sekitar 490 Hz untuk Arduino)
- Fungsi ini mengatur duty cycle (dari 0 hingga 255):
  - Nilai 0 = 0% ON, 100% OFF -> LED mati
  - Nilai 127 = ~50% ON, 50% OFF -> LED setengah terang
  - Nilai 255 = 100% ON, 0% OFF -> LED penuh terang
- Karena frekuensi sangat tinggi, mata manusia tidak bisa melihat kedipan, hanya melihat kecerahan rata-rata
- Semakin tinggi duty cycle, semakin banyak energi yang diterima LED, semakin terang LED tersebut

## 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?

Hubungannya adalah pemetaan linear menggunakan fungsi map():

```cpp
pwm = map(nilaiADC,
          0,     // ADC min
          1023,  // ADC max
          0,     // PWM min
          255);  // PWM max
```

Penjelasan:
- Rentang ADC: Potensiometer menghasilkan nilai 0–1023 (hasil pembacaan 10-bit ADC Arduino)
- Rentang PWM: Arduino hanya memahami perintah PWM 0–255 (8-bit)
- Fungsi map() melakukan konversi proporsional:
  - Nilai ADC 0 → PWM 0 (LED mati)
  - Nilai ADC 1023 → PWM 255 (LED maksimal terang)
  - Nilai ADC di antaranya dipetakan proporsional

Rumus di map():
$$PWM = \frac{(ADC - 0) \times (255 - 0)}{1023 - 0} = \frac{ADC \times 255}{1023}$$

Ini memastikan perubahan posisi potensiometer menyebabkan perubahan kecerahan LED secara halus dan proporsional.

## 3. Modifikasi program agar LED hanya menyala rentang PWM 50–200

Kode asli:
```cpp
pwm = map(nilaiADC,
          0,     // ADC min
          1023,  // ADC max
          0,     // PWM min
          255);  // PWM max

analogWrite(LED_PIN, pwm);
```

Kode yang dimodifikasi:
```cpp
pwm = map(nilaiADC,
          0,     // ADC min
          1023,  // ADC max
          0,     // PWM min
          255);  // PWM max

pwm = (pwm >= 50 && pwm <= 200) ? pwm : 0;  // kalau di range 50-200, gunakan pwm. jika tidak, set ke 0

analogWrite(LED_PIN, pwm);
```

Penjelasan:
- Ketika nilai PWM hasil map() berada di 50–200, LED akan menyala dengan kecerahan sesuai nilai PWM.
- Ketika nilai PWM < 50 atau > 200, LED MATI (PWM diset ke 0).
- Potensiometer tetap membaca 0–1023 penuh.

Hasil:
- Potensiometer di posisi yang menghasilkan PWM 50–200, LED menyala.
- Potensiometer di posisi lainnya, maka LED akan mati total.