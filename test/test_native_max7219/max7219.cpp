#include <unity.h>

#include <MAX7219.h>

#include "mock.h"

// for this test we use 3x2 array of 5x7 matrices
typedef LedMatrixDisplay::LedMatrix<5, 7> LedMatrix;
typedef LedMatrixDisplay::LedMatrixArray<LedMatrix, 3, 2> LedMatrixArray;

typedef LedMatrixDisplay::MAX7219::LedMatrixDisplayColumnAnode<LedMatrixArray, MAX7219_Mock> DisplayMAX7219CA;
DisplayMAX7219CA displayMAX7219CA;

typedef LedMatrixDisplay::MAX7219::LedMatrixDisplayColumnCathode<LedMatrixArray, MAX7219_Mock> DisplayMAX7219CC;
DisplayMAX7219CC displayMAX7219CC;

void test_display_ca_init()
{
    displayMAX7219CA.init();

    for (int i = 0; i < displayMAX7219CA.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(0, displayMAX7219CA.checkRegister(i, MAX7219_REG_DECODEMODE));
        TEST_ASSERT_EQUAL(displayMAX7219CA.matrixHeight, displayMAX7219CA.checkRegister(i, MAX7219_REG_SCANLIMIT));
        TEST_ASSERT_EQUAL(1, displayMAX7219CA.checkRegister(i, MAX7219_REG_SHUTDOWN));
        TEST_ASSERT_EQUAL(0, displayMAX7219CA.checkRegister(i, MAX7219_REG_DISPLAYTEST));
    }
}

void test_display_cc_init()
{
    displayMAX7219CC.init();

    for (int i = 0; i < displayMAX7219CC.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(0, displayMAX7219CC.checkRegister(i, MAX7219_REG_DECODEMODE));
        TEST_ASSERT_EQUAL(displayMAX7219CC.matrixWidth, displayMAX7219CC.checkRegister(i, MAX7219_REG_SCANLIMIT));
        TEST_ASSERT_EQUAL(1, displayMAX7219CC.checkRegister(i, MAX7219_REG_SHUTDOWN));
        TEST_ASSERT_EQUAL(0, displayMAX7219CC.checkRegister(i, MAX7219_REG_DISPLAYTEST));
    }
}

void test_display_ca_intensity()
{
    displayMAX7219CA.setIntensity(4);
    for (int i = 0; i < displayMAX7219CA.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(4, displayMAX7219CA.checkRegister(i, MAX7219_REG_INTENSITY));
    }

    displayMAX7219CA.setIntensity(0);
    for (int i = 0; i < displayMAX7219CA.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(0, displayMAX7219CA.checkRegister(i, MAX7219_REG_INTENSITY));
    }

    displayMAX7219CA.setIntensity(15);
    for (int i = 0; i < displayMAX7219CA.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(15, displayMAX7219CA.checkRegister(i, MAX7219_REG_INTENSITY));
    }
}

void test_display_cc_intensity()
{
    displayMAX7219CC.setIntensity(4);
    for (int i = 0; i < displayMAX7219CA.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(4, displayMAX7219CC.checkRegister(i, MAX7219_REG_INTENSITY));
    }

    displayMAX7219CC.setIntensity(0);
    for (int i = 0; i < displayMAX7219CA.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(0, displayMAX7219CC.checkRegister(i, MAX7219_REG_INTENSITY));
    }

    displayMAX7219CC.setIntensity(15);
    for (int i = 0; i < displayMAX7219CA.matrixCount; i++)
    {
        TEST_ASSERT_EQUAL(15, displayMAX7219CC.checkRegister(i, MAX7219_REG_INTENSITY));
    }
}

void test_display_ca_commit()
{
    displayMAX7219CA.clear();
    displayMAX7219CA.setPixel(2, 0);
    displayMAX7219CA.commit();

    TEST_ASSERT_EQUAL(4, displayMAX7219CA.checkRegister(0, MAX7219_REG_DIGIT0));
    TEST_ASSERT_EQUAL(0, displayMAX7219CA.checkRegister(0, MAX7219_REG_DIGIT2));

    displayMAX7219CA.clear();
    displayMAX7219CA.setPixel(6, 8);
    displayMAX7219CA.commit();

    TEST_ASSERT_EQUAL(2, displayMAX7219CA.checkRegister(4, MAX7219_REG_DIGIT1));
}

void test_display_cc_commit()
{
    displayMAX7219CC.clear();
    displayMAX7219CC.setPixel(0, 2);
    displayMAX7219CC.commit();

    TEST_ASSERT_EQUAL(4, displayMAX7219CC.checkRegister(0, MAX7219_REG_DIGIT0));
    TEST_ASSERT_EQUAL(0, displayMAX7219CC.checkRegister(0, MAX7219_REG_DIGIT2));

    displayMAX7219CC.clear();
    displayMAX7219CC.setPixel(6, 8);
    displayMAX7219CC.commit();

    TEST_ASSERT_EQUAL(2, displayMAX7219CC.checkRegister(4, MAX7219_REG_DIGIT1));
}

void run_tests_max7219()
{
    RUN_TEST(test_display_ca_init);
    RUN_TEST(test_display_cc_init);

    RUN_TEST(test_display_ca_intensity);
    RUN_TEST(test_display_cc_intensity);

    RUN_TEST(test_display_ca_commit);
    RUN_TEST(test_display_cc_commit);
}
