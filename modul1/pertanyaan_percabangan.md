# Jawaban Pertanyaan Percabangan

## 1) Pada kondisi apa program masuk ke blok `if`?
Program masuk ke blok `if` saat nilai `timeDelay <= 100`.

Artinya, ketika delay sudah dipercepat terus-menerus sampai 100 ms atau kurang, maka bagian `if` dijalankan untuk melakukan jeda 3 detik lalu mereset `timeDelay` ke 1000 ms.

## 2) Pada kondisi apa program masuk ke blok `else`?
Program masuk ke blok `else` saat kondisi `timeDelay <= 100` **tidak terpenuhi**,
yaitu ketika `timeDelay > 100`.

Di bagian ini program melakukan `timeDelay -= 100`, sehingga kedipan LED makin cepat setiap siklus.

## 3) Apa fungsi dari perintah `delay(timeDelay)`?
Fungsi `delay(timeDelay)` adalah memberi jeda selama nilai `timeDelay` (dalam milidetik).

Pada kode ini, `delay(timeDelay)` dipakai setelah LED menyala dan setelah LED mati, sehingga:
- lama LED menyala ditentukan oleh `timeDelay`
- lama LED mati juga ditentukan oleh `timeDelay`
- saat `timeDelay` makin kecil, kedipan LED terasa makin cepat

## 4) Ubah alur menjadi: cepat -> sedang -> mati (tanpa langsung reset)
Di bawah ini contoh kode yang mengubah alur agar LED **tidak langsung reset** ke lambat lagi, tetapi berjalan:
**cepat -> sedang -> mati**.

```cpp
const int ledPin = 12; 
int timeDelay = 1000;
int state = 0;

void setup() { 
  pinMode(ledPin, OUTPUT);
} 

void loop() { 
  
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);
  
  digitalWrite(ledPin, LOW);
  delay(timeDelay);

  
  if (state == 0) {
    timeDelay -= 100; 
    
    if (timeDelay <= 200) { 
      state = 1; 
    }
  } 
  else if (state == 1) { 
    timeDelay += 100; 
    
    if (timeDelay >= 500) { 
      state = 2; 
    }
  } 
  else if (state == 2) { 
    delay(3000); 
    timeDelay = 1000; 
    state = 0; 
  }
}
```

### Penjelasan Kode Baru

```cpp
const int ledPin = 12;
```
Menentukan bahwa LED terhubung pada pin digital 12, dan const berarti nilai ini tidak akan berubah selama program berjalan.

```cpp
int timeDelay = 1000;
```
Menyimpan nilai delay (waktu jeda) dalam milidetik dengan nilai awal 1000 ms (1 detik).

```cpp
int state = 0;
```
- Menyimpan kondisi (state) sistem.
- Digunakan untuk mengatur alur perubahan kecepatan LED.
- Nilai state: 0 → fase percepatan (lambat → cepat), 1 → fase perlambatan (cepat → sedang), 2 → fase reset

```cpp
void setup() { 
  pinMode(ledPin, OUTPUT);
}
```
Mengatur pin 12 sebagai output. Digunakan untuk mengontrol LED (nyala/mati).

```cpp
digitalWrite(ledPin, HIGH);
delay(timeDelay);
```
Mengatur lama waktu LED menyala sesuai nilai delay

```cpp
digitalWrite(ledPin, LOW);
delay(timeDelay);
```
Mengatur lama waktu LED mati sesuai nilai delay

```cpp
if (state == 0) {
  timeDelay -= 100;
```
Delay dikurangi 100 ms setiap siklus. LED akan berkedip semakin cepat.

```cpp
if (timeDelay <= 200) {
  state = 1;
}
```
Jika delay sudah sangat kecil (cepat), pindah ke state berikutnya.

```cpp
else if (state == 1) {
  timeDelay += 100;
```
Delay ditambah 100 ms setiap siklus. LED mulai melambat (menuju sedang).

```cpp
if (timeDelay >= 500) {
  state = 2;
}
```
Jika delay mencapai 500 ms (sedang), pindah ke state berikutnya.

```cpp
else if (state == 2) {
  delay(3000);
```
Program berhenti selama 3 detik sebelum reset.

```cpp
timeDelay = 1000;
state = 0;
```
Delay dikembalikan ke nilai awal (lambat), dan state di-reset ke awal (0).