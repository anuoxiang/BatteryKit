#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <TimerOne.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
int cells[] = {A0, A1, A2, A3, A6, A7};

float rates[] = { 1.0
                  , (1000.0 + 1000.0) / 1000.0
                  , (2000.0 + 1000.0) / 1000.0
                  , (3300.0 + 1000.0) / 1000.0
                  , (4700.0 + 1000.0) / 1000.0
                  , (5100.0 + 1000.0) / 1000.0
                };
int ledPin = 13;      // select the pin for the LED

#define CONTRAST 45
#define RATE1 1
#define RATE2 0

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  Timer1.initialize(1000000);
  //Timer1.attachInterrupt(checker);
  display.begin();
  display.setContrast(CONTRAST);
  display.setRotation(1);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  //display.setCursor(0,0);
  //display.println("100%");
  //display.println("3.74V");
  //display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the value from the sensor:
  int sensorValues[6];
  display.clearDisplay();
  display.setCursor(0, 0);
  float voltage[6];
  for (int8_t i = 0; i < 6; i++) {
    sensorValues[i] = analogRead(cells[i]);
    if (sensorValues[i] < 100) break;
    if (i > 0) {
      voltage[i] = sensorValues[i] * (5.0 / 1023.0) * rates[i];
      for ( int8_t j = i - 1; j >= 0; j--) {
        voltage[i] -= voltage[j];
      }
    }
    else
      voltage[i] = sensorValues[i] * (5.0 / 1023.0) * rates[i];

    Serial.print(voltage[i]);
    display.print(voltage[i]);
    display.println("V");
    Serial.print("\t");
  }
  display.display();
  Serial.println();
  delay(1000);
}

//检测电压，绘制到屏幕上
void checker() {

}

void drawCell(uint8_t i, float voltage) {

}

