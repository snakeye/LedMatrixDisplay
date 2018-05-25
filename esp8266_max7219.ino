#include <Arduino.h>

#include "max7219.h"
#include "font.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN 2

typedef MAX7219_Display<CS_PIN, NUMBER_OF_DEVICES, Font> Display;

Display display = Display();

void setup() {
  Serial.begin(115200); // For debugging output

  display.init();
  display.setBrightness(15); // range is 0-15
  //display.setText("MAX7219 Demo");
}

void loop() {
  display.clear();


  display.setPixel(0, 0);

  //display.scrollTextLeft();
  //display.drawText();

  display.commit(); // commit transfers the byte buffer to the displays

  delay(1000);
}

