#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define OLED_RESET 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; 
float R2 = 10000.0;  
int value = 0;
int a[5] = {};


void setup() {
  pinMode(analogInput, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
}


void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("  voltage  \n  ");
  value = analogRead(analogInput);
  vout = (value * 5) / 1024.0;
  vin = vout / (R2 / (R1 + R2));
  if (vin < 0.09) {
    vin = 0.0;
  }
  display.print(vin);
  delay(500);
  display.display();
}
