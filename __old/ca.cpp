#include <unity.h>
#include "arduino_mock.h"

#include <LedMatrix.h>

typedef MAX7219::LedMatrixDisplay<MAX7219::LedMatrixCommonAnode<5, 7>, 1, 1, MAX7219::MAX7219_Mock> LedMatrixDisplay;

LedMatrixDisplay displayCA;

void test_init_ca() {
    displayCA.init();

    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_SCANLIMIT), 7);
}

void test_set_pixel_ca()
{
    displayCA.clear();
    displayCA.setPixel(0, 2);
    displayCA.commit();

    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT0), 1);
    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT1), 0);
    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT2), 0);
    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT3), 0);
    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT4), 0);
    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT5), 0);
    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT6), 0);
    TEST_ASSERT_EQUAL(displayCA.checkRegister(MAX7219_REG_DIGIT7), 0);
}

void run_tests_ca()
{
    RUN_TEST(test_init_ca);
    RUN_TEST(test_set_pixel_ca);
}