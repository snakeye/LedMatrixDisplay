#include <unity.h>

#include <Arduino.h>

#include <arduino/LedMatrixDisplay_Arduino.h>

typedef LedMatrixDisplay::LedMatrix<8, 8> LedMatrix;
typedef LedMatrixDisplay::LedMatrixArray<LedMatrix, 5, 1> LedMatrixArray;

typedef LedMatrixDisplay::MAX7219::Arduino::LedMatrixDisplayColumnAnodeSPI<LedMatrixArray, 16> Display;
Display display;

void test_display()
{
    display.init();
    display.clear();
    display.setPixel(3, 0);
    display.setPixel(0, 2);
    display.commit();
}

void setup()
{
    UNITY_BEGIN();

    test_display();

    UNITY_END();
}

void loop()
{
}
