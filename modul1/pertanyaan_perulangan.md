# Jawaban Pertanyaan Perulangan LED

## 1) Gambarkan rangkaian schematic 5 LED running

Berikut adalah rangkaian schematic LED running dengan 5 LED yang terhubung ke Arduino.

Konfigurasi Rangkaian:
- LED 1 -> Pin 2
- LED 2 -> Pin 3
- LED 3 -> Pin 4
- LED 4 -> Pin 5
- LED 5 -> Pin 6

➔ Pin 2, 3, 4, 5, 6 dari Arduino terhubung ke Anoda (+) masing-masing LED
<br>➔ Katode (-) LED dihubungkan ke resistor 220Ω
<br>➔ Resistor dihubungkan ke GND
```

---

## 2) Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan

Program membuat efek LED berjalan dari kiri ke kanan melalui **looping for** dari pin 2 ke pin 6:

```cpp
for (int ledPin = 2; ledPin < 7; ledPin++) {
    digitalWrite(ledPin, HIGH);  // Nyalakan LED pin sekarang
    delay(timer);                // Tunggu 100ms
    digitalWrite(ledPin, LOW);   // Matikan LED pin
}
```

**Penjelasan alur:**
1. Looping dimulai dari `ledPin = 2` (LED paling kiri)
2. Setiap iterasi: nyalakan LED → tunggu 100ms → matikan LED
3. `ledPin++` membuat looping increment, sehingga urutan nyala: 2 → 3 → 4 → 5 → 6
4. Efek visualnya: LED bergerak dari **kiri ke kanan** seolah-olah ada cahaya yang berjalan

---

## 3) Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri

Program membuat LED kembali dari kanan ke kiri melalui **looping for decrement** dari pin 6 ke pin 2:

```cpp
for (int ledPin = 6; ledPin >= 2; ledPin--) {
    digitalWrite(ledPin, HIGH);  // Nyalakan LED pin sekarang
    delay(timer);                // Tunggu 100ms
    digitalWrite(ledPin, LOW);   // Matikan LED pin
}
```

**Penjelasan alur:**
1. Looping dimulai dari `ledPin = 6` (LED paling kanan)
2. Kondisi loop: `ledPin >= 2` (terus looping selama pin ≥ 2)
3. `ledPin--` membuat looping decrement, sehingga urutan nyala: 6 → 5 → 4 → 3 → 2
4. Efek visualnya: LED bergerak dari **kanan ke kiri**, membuat efek "running" bolak-balik

---

## 4) Program LED berubah: 3 LED kanan dan 3 LED kiri bergantian

Berikut kode untuk membuat 3 LED sebelah kanan dan 3 LED sebelah kiri menyala bergantian:

```cpp
int timer = 100;  // Delay timer untuk kecepatan menyala

void setup() {
  // Inisialisasi 6 LED pada pin 2-7
  for (int ledPin = 2; ledPin < 8; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
}

void loop() {

  // kiri nyalakan
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(timer); 
  
  // kiri matikan
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  // kanan nyalakan
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(timer);
  
  // kanan matikan
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
```

### Penjelasan Kode Per Baris:

**Setup:**
```cpp
for (int ledPin = 2; ledPin < 8; ledPin++)
```
Loop inisialisasi 6 LED dari pin 2 sampai 7

```cpp
pinMode(ledPin, OUTPUT)
```
Set setiap pin sebagai output agar bisa mengontrol LED

**Loop Main:**
- **Blok 1 (3 LED Kiri Menyala):**
```cpp
digitalWrite(2, HIGH)
digitalWrite(3, HIGH)
digitalWrite(4, HIGH)
```
Kirim sinyal ke pin 2 sampai 4 untuk menyelakan LED

```cpp
delay(timer)
```
Tunggu 100ms, semua LED kiri tetap menyala
   
- **Mematikan 3 LED Kiri:**
```cpp
digitalWrite(2, LOW)
digitalWrite(3, LOW)
digitalWrite(4, LOW)
```
Kirim sinyal LOW ke semua LED kiri (2, 3 , 4), LED padam

- **Blok 2 (3 LED Kanan Menyala):**
```cpp
digitalWrite(5, HIGH) 
digitalWrite(6, HIGH)
digitalWrite(7, HIGH)
```
Kirim sinyal ke pin 5 sampai 7, LED menyala
   
```cpp
delay(timer)
```
Tunggu 100ms, semua LED kanan tetap menyala

- **Mematikan 3 LED Kanan:**
```cpp
digitalWrite(5, LOW)
digitalWrite(6, LOW)
digitalWrite(7, LOW)
```
Kirim sinyal LOW ke semua LED kanan (5, 6 , 7), LED padam