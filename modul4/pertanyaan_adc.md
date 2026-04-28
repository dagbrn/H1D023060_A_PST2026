## 1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?

Perintah analogRead() berfungsi untuk membaca nilai tegangan analog dari potensiometer yang terhubung ke pin ADC (A0). 

Alur secara spesifik:
- Membaca sinyal analog dari pin potensioPin (A0)
- Mengkonversi sinyal analog menjadi nilai digital dalam rentang **0–1023**
  - Nilai 0 = 0V (tegangan minimum)
  - Nilai 1023 = 5V (tegangan maksimum)
- Dalam program ini, val = analogRead(potensioPin) menyimpan hasil pembacaan potensiometer, sehingga perubahan posisi potensiometer akan menghasilkan nilai ADC yang berbeda

## 2. Mengapa diperlukan fungsi map() dalam program tersebut?

Fungsi map() diperlukan untuk mengkonversi rentang nilai ADC ke rentang nilai yang sesuai dengan kebutuhan servo motor.

Alasan penggunaan:
- Rentang ADC: Potensiometer menghasilkan nilai 0–1023
- Rentang Servo: Servo motor hanya memahami perintah sudut 0–180 derajat
- Fungsi map() melakukan pemetaan linear dari rentang sumber ke rentang tujuan, sehingga:
  - Nilai ADC 0 → Sudut servo 0°
  - Nilai ADC 1023 → Sudut servo 180°
  - Nilai ADC di antaranya dipetakan secara proporsional

Tanpa map(), kita harus melakukan konversi manual dengan rumus yang lebih rumit.

## 3. Modifikasi program agar servo hanya bergerak 30°–150°

Ubah bagian konversi data dalam fungsi loop():

Kode asli:
```cpp
pos = map(val,
           0,     // nilai minimum ADC
           1023,  // nilai maksimum ADC
           0,     // sudut minimum servo
           180);  // sudut maksimum servo
```

Kode yang dimodifikasi:
```cpp
pos = map(val,
           0,     // nilai minimum ADC
           1023,  // nilai maksimum ADC
           30,    // sudut minimum servo (diubah dari 0 menjadi 30)
           150);  // sudut maksimum servo (diubah dari 180 menjadi 150)
```

Penjelasan:
- Dengan perubahan ini, potensiometer tetap membaca ADC 0–1023
- Namun servo hanya akan bergerak dalam rentang 30°–150° (bukan 0°–180°)
- Ketika potensiometer di posisi minimum (ADC = 0) → servo di 30°
- Ketika potensiometer di posisi maksimum (ADC = 1023) → servo di 150°
- Pergerakan servo dibatasi untuk mencegah mekanisme tertentu yang mungkin ada di rangkaian praktikum ini
