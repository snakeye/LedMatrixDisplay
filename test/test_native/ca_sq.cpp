#include <unity.h>
#include "arduino_mock.h"

#include <LedMatrix.h>

typedef MAX7219::LedMatrixDisplay<MAX7219::LedMatrixCommonAnodeSquare, 1, 1, MAX7219::MAX7219_Mock> LedMatrixDisplay;

LedMatrixDisplay displayCASq;

void test_set_pixel_ca_sq()
{
    displayCASq.clear();
    displayCASq.setPixel(0, 2);
    displayCASq.commit();

    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT0), 1);
    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT1), 0);
    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT2), 0);
    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT3), 0);
    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT4), 0);
    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT5), 0);
    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT6), 0);
    TEST_ASSERT_EQUAL(displayCASq.checkRegister(MAX7219_REG_DIGIT7), 0);
}

void run_tests_ca_sq()
{
    RUN_TEST(test_set_pixel_ca_sq);
}