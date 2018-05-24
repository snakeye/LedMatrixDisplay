#include <Arduino.h>
//#include <SPI.h>

#include "max7219.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN 2

typedef MAX7219_Display<MAX7219_Driver_CommonAnode> CA_Display;
typedef MAX7219_Display<MAX7219_Driver_CommonCathode> CC_Display;

CA_Display display = CA_Display();

void setup() {
  Serial.begin(115200); // For debugging output

  display.init();
  display.setBrightness(15); // range is 0-15
  display.setText("MAX7219 Demo");
}

void loop() {
  display.clear();
  
  //display.scrollTextLeft();
  display.drawText();
  
  display.commit(); // commit transfers the byte buffer to the displays
  
  delay(10);
}

