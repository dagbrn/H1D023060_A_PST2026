#include <Arduino.h>

const int segmentPins[8] = {11, 10, 7 ,13, 12, 8, 9, 6};
const int pushBtn = 2;
int ledRed = 3;
int ledYellow = 4;
int ledGreen = 5;

byte digitPattern[16][8] = {

{1,1,1,1,1,1,0,0}, //0
{0,1,1,0,0,0,0,0}, //1
{1,1,0,1,1,0,1,0}, //2
{1,1,1,1,0,0,1,0}, //3
{0,1,1,0,0,1,1,0}, //4
{1,0,1,1,0,1,1,0}, //5
{1,0,1,1,1,1,1,0}, //6
{1,1,1,0,0,0,0,0}, //7
{1,1,1,1,1,1,1,0}, //8
{1,1,1,1,0,1,1,0}, //9
{1,1,1,0,1,1,1,0}, //A
{0,0,1,1,1,1,1,0}, //b
{1,0,0,1,1,1,0,0}, //C
{0,1,1,1,1,0,1,0}, //d
{1,0,0,1,1,1,1,0}, //E
{1,0,0,0,1,1,1,0}  //F
};

int currentDigit = 9;

void displayDigit(int num)
{
  for(int i=9;i>=0;i--)
  {
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup() {
  for(int i=9;i>=0;i--)
  {
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(pushBtn, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT); 
  pinMode(ledYellow, OUTPUT); 
  pinMode(ledGreen  , OUTPUT); 
}

void loop() {
  
  digitalWrite(ledGreen, HIGH);

  bool isClicked = digitalRead(pushBtn);

  if(isClicked){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH;
    
    displayDigit(currentDigit);
    if(currentDigit == 0) currentDigit = 9;

    displayWrite(ledRed, LOW);
    displayWrite(ledYellow, HIGH);
    delay(3000);

    digitalWrite(ledGreen, HIGH);
  }
}
