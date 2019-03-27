# ESP8266 MAX7219 Arduino

MAX7219/MAX7221 library for ESP8266 and Arduino platform

Based on https://github.com/squix78/MAX7219LedMatrix

## Example code

```cpp
#include <Arduino.h>

#include <LedMatrixDisplay.h>

using namespace LedMatrixDisplay;

// matrix type definition
typedef Matrix<8, 8> TMatrix;

// matrix array definition
typedef MatrixArray<TMatrix, 5, 1> TMatrixArray;

// canvas definition
typedef Canvas<TMatrixArray> TCanvas;

// display definition
typedef DisplayColumnCathode<TCanvas, 16> TDisplay;

TDisplay display;

void setup()
{
    display.init();
    display.setIntensity(2);
    display.clear();
    display.commit();
}

void loop()
{
    static int i = 0;

    display.clear();
    display.setPixel(i, 0);
    display.commit();

    i = (i + 1) % 40;

    delay(100);
}

```
