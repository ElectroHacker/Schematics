#include <Adafruit_SSD1306.h> 
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Keypad.h>

#define OLED_RESET 4                                  
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
                            {'1','2','3','A'},
                            {'4','5','6','B'},
                            {'7','8','9','C'},
                            {'*','0','#','D'}
                                              };                         
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad electroKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int override = 12;
String code = "";
String password = "828486";
int pass_len = password.length();
int flag = 0;


void setup() {
  
  pinMode(override, INPUT);
  
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);           
  
  delay(2000);                                        
  
  display.clearDisplay();                             
  display.setTextSize(2);                             
  display.setTextColor(WHITE);                        
  display.setCursor(0,0);                             
  display.print(" Enter Key\n\n  ");
  display.display();                                   
}


void loop() {
  
  char electroKey = electroKeypad.getKey();
  if (digitalRead(override) == HIGH) {
    int task_completed = 0;
    for (int i = 0; i <= 60; i++) {
      delay(50);
      if (digitalRead(override) == HIGH) {
        if (task_completed == 60) {
          display.clearDisplay();
          display.setCursor(0,0);  
          display.print("\n Unlocked");
          display.display();
          digitalWrite(11, HIGH);
          digitalWrite(10, HIGH);
          delay(500);
          digitalWrite(10, LOW);
          delay(4000);
          digitalWrite(10, HIGH);
          delay(500);
          digitalWrite(11, LOW);
          digitalWrite(10, LOW);
        }
        task_completed += 1;
      }
    }
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(" Enter Key\n\n  ");
    display.display();
  }
  
  if (electroKey) {
    if (electroKey == 'B') {
      code = code.substring(0, code.length() - 1);
      display.clearDisplay();
      display.setCursor(0,0);
      display.print(" Enter Key\n\n  ");
      for (int i = 0; i < code.length(); i++) {
        display.print("*");    
      }
      display.display();
      flag = 0;
    } else if (electroKey == 'C') {
      code = "";
      display.clearDisplay();
      display.setCursor(0,0);
      display.print(" Enter Key\n\n  ");
      display.display();
      flag = 0;
    } else if ((code.length() < pass_len) && (electroKey != 'A')) {
      display.print("*");
      code += electroKey;
      display.display();
    }
    if (code.length() == pass_len) {
      if (flag == 1) {
        if (electroKey == 'A') {
          if (code.equals(password)) {
            display.clearDisplay();
            display.setCursor(0,0);
            display.print("\n Unlocked");
            display.display();
            digitalWrite(11, HIGH);
            digitalWrite(10, HIGH);
            delay(500);
            digitalWrite(10, LOW);
            delay(4000);
            digitalWrite(10, HIGH);
            delay(500);
            digitalWrite(11, LOW);
            digitalWrite(10, LOW);
          } else {
            display.clearDisplay();
            display.setCursor(0,0);
            display.print("\n Fuck Off");
            display.display();
            delay(5000);
          }
        } else {
          display.clearDisplay();
          display.setCursor(0,0);
          display.print("\n Fuck Off");
          display.display();
          delay(5000);
        }
        flag = 0;
        code = "";
        display.clearDisplay();
        display.setCursor(0,0);
        display.print(" Enter Key\n\n  ");
        display.display();
      } else {
        flag = 1;
      }  
    }
  }  
}
