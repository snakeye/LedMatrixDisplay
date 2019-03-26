# ESP8266 MAX7219 Arduino

MAX7219/MAX7221 library for ESP8266 and Arduino platform

Based on https://github.com/squix78/MAX7219LedMatrix

## Example code

```cpp
#include <Arduino.h>

#include <LedMatrix.h>

typedef LedMatrixDisplay::LedMatrix<8, 8> LedMatrix;
typedef LedMatrixDisplay::LedMatrixArray<LedMatrix, 5, 1> LedMatrixArray;

typedef LedMatrixDisplay::MAX7219::Arduino::LedMatrixDisplayColumnAnodeSPI<LedMatrixArray, 16> Display;
Display display;

void setup()
{
    display.init();
    display.clear();
    display.setPixel(3, 0);
    display.setPixel(0, 2);
    display.commit();
}

void loop()
{
}
```
