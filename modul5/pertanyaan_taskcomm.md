## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task berjalan secara bersamaan dari perspektif pengguna, tetapi secara teknis berjalan bergantian atau context switching pada mikrokontroler single-core.

Mekanismenya:

- **FreeRTOS Scheduler**: Scheduler menjadwalkan eksekusi antara `read_data` dan `display` task.
- **Context Switching**: 
  - Ketika `read_data` memanggil `xQueueSend()`, task ini melepaskan CPU
  - FreeRTOS scheduler kemudian memberikan kesempatan kepada `display` task untuk berjalan
  - Ketika `display` memanggil `xQueueReceive()` dan menunggu data, task ini juga melepaskan CPU
  - Kembali ke `read_data` yang kemudian mengirimkan data berikutnya
- **Prioritas Task**: Kedua task memiliki prioritas yang sama (priority = 0)

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program ini relatif aman dari race condition karena menggunakan Queue (FreeRTOS) yang merupakan thread-safe data structure.

### Mengapa Tidak Ada Race Condition:

1. **Queue adalah Thread-Safe**:
   - `xQueueSend()` dan `xQueueReceive()` adalah operasi atomic yang dilindungi oleh FreeRTOS kernel
   - Kernel menggunakan mutex atau critical section secara internal
   - Hanya satu task yang dapat mengakses queue pada waktu tertentu

2. **Synchronization Mechanism**:
   - `xQueueSend()`: Mengirim data ke queue (blocking jika full)
   - `xQueueReceive()`: Menerima data dari queue (blocking jika kosong)
   - Kedua operasi ini saling tersinkronisasi

3. **Struct adalah Value Type**:
   - Struct `readings` dicopy ke queue, bukan reference
   - Tidak ada shared mutable state yang bisa diakses oleh dua task secara bersamaan

## 3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya?

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2           // pin data DHT11 terhubung ke pin 2
#define DHTTYPE DHT22      // tipe dht yang digunakan

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float h;
};

QueueHandle_t my_queue;

void setup() {
  Serial.begin(9600);
  delay(2000);  // menunggu sensor siap
  
  Serial.println("Initializing DHT sensor...");
  dht.begin();
  
  // create queue dengan size 3 untuk buffer data
  my_queue = xQueueCreate(3, sizeof(struct readings));
  
  xTaskCreate(read_data, "read sensors", 256, NULL, 1, NULL);
  xTaskCreate(display, "display", 128, NULL, 2, NULL);
  
  vTaskStartScheduler();
}

void loop() {}

// task untuk membaca sensor DHT Baca data setiap 2 detik
void read_data(void *pvParameters) {
  struct readings x;
  int errorCount = 0;
  
  for(;;) {
    // baca suhu (Celsius)
    float temperature = dht.readTemperature();
    
    // baca kelembaban
    float humidity = dht.readHumidity();
    
    // cek apakah pembacaan valid
    if (isnan(temperature) || isnan(humidity)) {
      errorCount++;
      Serial.print("DHT read error! Count: ");
      Serial.println(errorCount);
      
      // retry jika error, tapi dengan delay lebih lama
      vTaskDelay(3000 / portTICK_PERIOD_MS);
      continue;
    }
    
    // reset error counter
    errorCount = 0;
    
    // simpan data ke struct
    x.temp = temperature;
    x.h = humidity;
    
    // kirim ke queue
    // xQueueSend dengan timeout 0 agar tidak blocking indefinitely
    if (xQueueSend(my_queue, &x, 0) != pdPASS) {
      Serial.println("Queue full - dropping old data");
    }
    
    Serial.println("Data sent to queue");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

 // task untuk menampilkan data dari queue. prioritas lebih tinggi agar responsif

void display(void *pvParameters) {
  struct readings x;
  int displayCount = 0;
  
  for(;;) {
    // get data dari queue dengan blocking indefinite
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
      displayCount++;
      
      Serial.println("=====================================");
      Serial.print("Display #: ");
      Serial.println(displayCount);
      Serial.print("Temperature: ");
      Serial.print(x.temp);
      Serial.println(" °C");
      Serial.print("Humidity: ");
      Serial.print(x.h);
      Serial.println(" %");
      Serial.print("Heat Index: ");
      
      // hitung heat index (terasa lebih panas pada kelembaban tinggi)
      float heatIndex = dht.computeHeatIndex(x.temp, x.h, false);
      Serial.print(heatIndex);
      Serial.println(" °C");
      Serial.println("=====================================");
    }
  }
}
```

### Hasil yang Diharapkan:

**Output Serial Monitor:**
```
Initializing DHT sensor...
Data sent to queue
=====================================
Display #: 1
Temperature: 28.50 °C
Humidity: 65.00 %
Heat Index: 32.10 °C
=====================================
Data sent to queue
=====================================
Display #: 2
Temperature: 28.80 °C
Humidity: 64.50 %
Heat Index: 32.35 °C
=====================================
```