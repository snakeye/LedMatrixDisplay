#include <unity.h>
#include "arduino_mock.h"

#include <MAX7219.h>

// for this test we use 3x2 array of 5x7 matrices
typedef LedMatrixDisplay::LedMatrix<5, 7> LedMatrix;
typedef LedMatrixDisplay::LedMatrixArray<LedMatrix, 3, 2> LedMatrixArray;
typedef LedMatrixDisplay::MAX7219::LedMatrixDisplayMAX7219<LedMatrixArray> DisplayMAX7219;

DisplayMAX7219 displayMAX7219;

void test_display_init()
{
    displayMAX7219.init();
}

void run_tests_max7219()
{
    RUN_TEST(test_display_init);
}
