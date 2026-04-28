#define POT_PIN A0
#define LED_PIN 9

int nilaiADC = 0;
int pwm = 0;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // read potensio
  nilaiADC = analogRead(POT_PIN);

  // processing data 
  pwm = map(nilaiADC,
            0,     // ADC min
            1023,  // ADC max
            0,     // PWM min
            255);  // PWM max

  // pwm output
  analogWrite(LED_PIN, pwm);

  // output to serial monitor
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50);
}