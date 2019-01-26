#include <unity.h>
#include "arduino_mock.h"

#include <LedMatrix.h>

typedef MAX7219::LedMatrixDisplay<MAX7219::LedMatrixCommonCathodeSquare, 1, 1, MAX7219::Test> LedMatrixDisplay;

LedMatrixDisplay display;

void test_init()
{
    display.init();

    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_SCANLIMIT), 8);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DECODEMODE), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DISPLAYTEST), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_INTENSITY), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_SHUTDOWN), 1);
}

void test_intensity()
{
    display.setIntensity(4);

    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_INTENSITY), 4);
}

void test_clear()
{
    display.clear();
    display.commit();

    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT0), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT1), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT2), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT3), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT4), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT5), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT6), 0);
    TEST_ASSERT_EQUAL(display.checkRegister(MAX7219_REG_DIGIT7), 0);
}

void test_framebuffer_pixel()
{
    display.clear();
    display.setPixel(0, 1);

    TEST_ASSERT_EQUAL(display.getPixel(0, 1), 1);
}

void run_tests_common()
{
    RUN_TEST(test_init);
    RUN_TEST(test_intensity);
    RUN_TEST(test_clear);
}
