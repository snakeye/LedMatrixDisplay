#include <unity.h>

#include <arduino/LedMatrixDisplay_Arduino.h>

typedef LedMatrixDisplay::LedMatrix<8, 8> LedMatrix;
typedef LedMatrixDisplay::LedMatrixArray<LedMatrix, 5, 1> LedMatrixArray;

typedef LedMatrixDisplay::MAX7219::Arduino::LedMatrixDisplayColumnAnodeY<LedMatrixArray> Display;
Display display;

void test_display()
{
    display.init();
    display.clear();
    display.setPixel(3, 0);
    display.setPixel(0, 2);
    display.commit();
}

void run_tests()
{
    UNITY_BEGIN();

    test_display();

    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>

void setup()
{
    run_tests();
}

void loop()
{
}

#else

int main(int argc, char **argv)
{
    return 0;
}

#endif