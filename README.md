# ESP8266 MAX7219 Arduino
MAX7219/MAX7221 library for ESP8266 and Arduino platform

Based on https://github.com/squix78/MAX7219LedMatrix

## Example code

```cpp
#include <SPI.h>
#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN 2

typedef MAX7219::PinAssignment<CS_PIN> PinAssignment;
typedef MAX7219::LedMatrix<NUMBER_OF_DEVICES, PinAssignment> LedMatrix;

LedMatrix ledMatrix = LedMatrix();
Font font = Font();

void setup() {
  Serial.begin(115200); // For debugging output
  ledMatrix.init();
  ledMatrix.setFont(&font);
  ledMatrix.setIntensity(4); // range is 0-15
  ledMatrix.setText("MAX7219 Demo");
}

void loop() {
  ledMatrix.clear();
  ledMatrix.scrollTextLeft();
  ledMatrix.drawText();
  ledMatrix.commit(); // commit transfers the byte buffer to the displays
  delay(200);
}
```
