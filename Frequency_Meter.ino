#include <Wire.h>                                     //I2C library for the OLED
#include <Adafruit_GFX.h>                             //To Display on oled
#include <Adafruit_SSD1306.h>                         //OLED driver
#include <FreqCount.h>                                //FreqCount library for counting frequencies
                                                      
 
#define OLED_RESET 4                                  
#define SCREEN_WIDTH 128 // OLED display width,(pixels)
#define SCREEN_HEIGHT 64 // OLED display height,(pixels)

// Declaration for SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
 
void setup()   {                
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);          //Address for that... OLED 
  display.display();                                  //show the buffer
  delay(2000);                                        //just wait
  display.clearDisplay();                             //smoothens the display quite well
  FreqCount.begin(1000);                              //let's begin 
}
 
 
void loop() {
 
 
  if (FreqCount.available()) {                        //if the viod setup is working
    float count = FreqCount.read();                   //creates float variable called count and fills it with current frequency count
    float period = (1/count);                         //creates float variable called period and fills it with the inverse of the frequency
  display.clearDisplay();                             //always clear the display first or it will fill your display with loads of crap
  display.setTextSize(1);                             //smallest text size because that's what fits well
  display.setTextColor(WHITE);                        //only color available
  display.setCursor(0,0);                             //cursor to top left
  display.println("Frequency Meter");                 //That's the heading, looks cool huh!
  display.println("--------- -----");                 //nothing just trash
  display.println("");                                //skips a line
  display.println("Frequency:");                      //prints the name of the function
  display.print(count);                               //prints the actual counted frequency
  display.println(" Hz");                             //prints units and drops down a line
  display.println();                                  //next line
  display.println("Period:");                         //prints the name of the fuction
  display.print(period*1000);                         //prints the period of signal in milliseconds
  display.print(" mS");                               //prints the units
  display.display();                                  //DON'T SHOW THE BUFFER!!!!
  }
  
  
  
}                                                     //THAT'S ALL, NOW PISS OFF.
