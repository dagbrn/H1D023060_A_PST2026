## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Dari perspektif user ketiga task berjalan secara bersamaan , tetapi secara teknis berjalan bergantian pada mikrokontroler single-core.

Mekanismenya:
- **FreeRTOS Scheduler**: FreeRTOS adalah Real-Time Operating System yang menyediakan scheduler untuk mengelola eksekusi multiple tasks
- **Context Switching**: Pada hardware single-core seperti Arduino, hanya satu task yang benar-benar berjalan di CPU pada waktu tertentu
- **Time Slicing**: Scheduler memberikan jatah waktu CPU kepada setiap task secara bergantian. Ketika task melakukan `vTaskDelay()`, task tersebut melepaskan CPU sehingga task lain dapat dijalankan
- **Prioritas**: Ketiga task dalam kode ini memiliki prioritas yang sama (priority = 1)

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!


Pertama tambahkan deklarasi fungsi di bagian awal, seperti `void TaskBlink4( void *pvParameters );`. Lalu cantumkan task baru di dalam `setup()` dengan menggunakan `xTaskCreate()` beserta parameter parameternya, misal `xTaskCreate(TaskBlink4, "task4", 128, NULL, 1, NULL);`

Parameter-parameter:
- **"TaskBlink4"**: Pointer ke fungsi task
- **"task4"**: Nama task
- **128**: Stack size untuk task
- **NULL**: Parameter yang diteruskan ke task
- **1**: Prioritas task
- **NULL**: Handle untuk task

Terakhir, implementasikan fungsi task tersebut dengan menambahkan implementasi task di akhir file:
```cpp
void TaskBlink4(void *pvParameters) {
  pinMode(6, OUTPUT);  // Pastikan menggunakan pin yang berbeda
  while(1) {
    Serial.println("Task4");
    digitalWrite(6, HIGH);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    digitalWrite(6, LOW);
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}
```

## 3. Modifikasilah program dengan menambah sensor potensiometer, lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya?

```cpp
#include <Arduino_FreeRTOS.h>

// deklarasi fungsi task
void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void Taskprint( void *pvParameters );
void TaskReadPotensio( void *pvParameters );

// volatile digunakan karena dua variabel ini diakses dari multiple task
volatile int potValue = 0; // variabel untuk menyimpan nilai potensiometer
volatile int ledSpeed = 200;  // default kecepatan kedipan led

void setup() {
  Serial.begin(9600);
  
  // create all task
  xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL );
  xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL );
  xTaskCreate(Taskprint, "task3", 128, NULL, 1, NULL );
  xTaskCreate(TaskReadPotensio, "task4", 128, NULL, 1, NULL );
  
  vTaskStartScheduler();
}

void loop() {
}

void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);
  while(1) {
    Serial.println("Task1");
    digitalWrite(8, HIGH);
    vTaskDelay(ledSpeed / portTICK_PERIOD_MS); // menggunakan variable `ledSpeed` sebagai delay
    digitalWrite(8, LOW);
    vTaskDelay(ledSpeed / portTICK_PERIOD_MS); // menggunakan variable `ledSpeed` sebagai delay
  }
}

void TaskBlink2(void *pvParameters) {
  pinMode(7, OUTPUT);
  while(1) {
    Serial.println("Task2");
    digitalWrite(7, HIGH);
    vTaskDelay(ledSpeed * 1.5 / portTICK_PERIOD_MS); // menggunakan variable `ledSpeed` sebagai delay
    digitalWrite(7, LOW);
    vTaskDelay(ledSpeed * 1.5 / portTICK_PERIOD_MS); // menggunakan variable `ledSpeed` sebagai delay
  }
}

void Taskprint(void *pvParameters) {
  int counter = 0;
  while(1) {
    counter++;
    Serial.print("Counter: ");
    Serial.print(counter);
    Serial.print(" | Pot Value: ");
    Serial.print(potValue);
    Serial.print(" | LED Speed: ");
    Serial.println(ledSpeed);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void TaskReadPotensio(void *pvParameters) {
  pinMode(A0, INPUT);  
  while(1) {
    // baca nilai analog dari A0 (0-1023)
    potValue = analogRead(A0);
    
    // mapping nilai 0-1023 menjadi range 50-500 ms
    ledSpeed = map(potValue, 0, 1023, 50, 500);

    // update setiap 100ms
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
```

### Hasilnya:

- **Ketika potensiometer di posisi minimum (0)**: LED berkedip cepat (~50ms)
- **Ketika potensiometer di posisi menengah (512)**: LED berkedip normal (~275ms)
- **Ketika potensiometer di posisi maksimum (1023)**: LED berkedip lambat (~500ms)
- **Serial Monitor** menampilkan: nilai potensiometer, kecepatan LED, dan counter
- **Kedua LED** akan berkedip dengan kecepatan yang dapat diatur