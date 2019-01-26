#include <unity.h>
#include "arduino_mock.h"

#include <LedMatrix.h>

typedef MAX7219::LedMatrixDisplay<MAX7219::LedMatrixCommonCathodeSquare, 1, 1, MAX7219::MAX7219_Mock> LedMatrixDisplay;

LedMatrixDisplay displayCCSq;

void test_set_pixel_cc_sq()
{
    displayCCSq.clear();
    displayCCSq.setPixel(0, 2);
    displayCCSq.commit();

    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT0), 1);
    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT1), 0);
    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT2), 0);
    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT3), 0);
    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT4), 0);
    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT5), 0);
    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT6), 0);
    TEST_ASSERT_EQUAL(displayCCSq.checkRegister(MAX7219_REG_DIGIT7), 0);
}

void run_tests_cc_sq()
{
    RUN_TEST(test_set_pixel_cc_sq);
}