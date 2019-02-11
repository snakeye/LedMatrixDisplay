#include <unity.h>

#include <LedMatrixDisplay.h>

#include "mock.h"

// for this test we use 3x2 array of 5x7 matrices
typedef LedMatrixDisplay::LedMatrix<5, 7> LedMatrix;
typedef LedMatrixDisplay::LedMatrixArray<LedMatrix, 3, 2> LedMatrixArray;
typedef LedMatrixDisplay::LedMatrixDisplay<LedMatrixArray> DisplayCommon;

DisplayCommon displayCommon;

void test_display_size()
{
    TEST_ASSERT_EQUAL(5, displayCommon.matrixWidth);
    TEST_ASSERT_EQUAL(7, displayCommon.matrixHeight);

    // correct number of matrices in rows and cols
    TEST_ASSERT_EQUAL(3, displayCommon.arrayCols);
    TEST_ASSERT_EQUAL(2, displayCommon.arrayRows);

    // correct number of matrices in general
    TEST_ASSERT_EQUAL(6, displayCommon.matrixCount);

    // correct size of the display in pixels
    TEST_ASSERT_EQUAL(15, displayCommon.width);
    TEST_ASSERT_EQUAL(14, displayCommon.height);
}

void test_clear()
{
    displayCommon.clear();

    // test if framebuffer is cleared
    for (int i = 0; i < displayCommon.width; i++)
    {
        for (int j = 0; j < displayCommon.height; j++)
        {
            TEST_ASSERT_EQUAL(0, displayCommon.getPixel(i, j));
        }
    }
}

void test_framebuffer_pixel()
{
    // left top corner
    displayCommon.clear();
    displayCommon.setPixel(3, 0);

    for (int i = 0; i < displayCommon.width; i++)
    {
        for (int j = 0; j < displayCommon.height; j++)
        {
            if (!(i == 3 && j == 0))
            {
                TEST_ASSERT_EQUAL(0, displayCommon.getPixel(0, 7));
            }
        }
    }
    TEST_ASSERT_EQUAL(1, displayCommon.getPixel(3, 0));

    // right top corner
    displayCommon.clear();
    displayCommon.setPixel(displayCommon.width - 1, 0);
    TEST_ASSERT_EQUAL(1, displayCommon.getPixel(displayCommon.width - 1, 0));

    // left bottom corner
    displayCommon.clear();
    displayCommon.setPixel(0, displayCommon.height - 1);
    TEST_ASSERT_EQUAL(1, displayCommon.getPixel(0, displayCommon.height - 1));

    // right bottom corner
    displayCommon.clear();
    displayCommon.setPixel(displayCommon.width - 1, displayCommon.height - 1);
    TEST_ASSERT_EQUAL(1, displayCommon.getPixel(displayCommon.width - 1, displayCommon.height - 1));
}

void run_tests_common()
{
    RUN_TEST(test_display_size);
    RUN_TEST(test_clear);
    RUN_TEST(test_framebuffer_pixel);
}
