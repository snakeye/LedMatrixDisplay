#include <unity.h>
#include "arduino_mock.h"

#include <LedMatrixDisplay.h>

// for this test we use 3x2 array of 5x7 matrices
typedef LedMatrixDisplay::LedMatrix<5, 7> LedMatrix;
typedef LedMatrixDisplay::LedMatrixArray<LedMatrix, 3, 2> LedMatrixArray;
typedef LedMatrixDisplay::LedMatrixDisplay<LedMatrixArray> DisplayCommon;

DisplayCommon displayCommon;

void test_display_size()
{
    // correct number of matrices in rows and cols
    TEST_ASSERT_EQUAL(displayCommon.matrixCols, 3);
    TEST_ASSERT_EQUAL(displayCommon.matrixRows, 2);

    // correct number of matrices in general
    TEST_ASSERT_EQUAL(displayCommon.matrixCount, 6);

    // correct size of the display in pixels
    TEST_ASSERT_EQUAL(displayCommon.width, 15);
    TEST_ASSERT_EQUAL(displayCommon.height, 14);
}

void test_clear()
{
    displayCommon.clear();

    // test if framebuffer is cleared
    for (int i = 0; i < displayCommon.width; i++)
    {
        for (int j = 0; j < displayCommon.height; j++)
        {
            TEST_ASSERT_EQUAL(displayCommon.getPixel(i, j), 0);
        }
    }
}

void test_framebuffer_pixel()
{
    // left top corner
    displayCommon.clear();
    displayCommon.setPixel(0, 0);
    TEST_ASSERT_EQUAL(displayCommon.getPixel(0, 0), 1);

    // right top corner
    displayCommon.clear(); 
    displayCommon.setPixel(displayCommon.width - 1, 0);
    TEST_ASSERT_EQUAL(displayCommon.getPixel(displayCommon.width - 1, 0), 1);

    // left bottom corner
    displayCommon.clear(); 
    displayCommon.setPixel(0, displayCommon.height - 1);
    TEST_ASSERT_EQUAL(displayCommon.getPixel(0, displayCommon.height - 1), 1);

    // right bottom corner
    displayCommon.clear(); 
    displayCommon.setPixel(displayCommon.width - 1, displayCommon.height - 1);
    TEST_ASSERT_EQUAL(displayCommon.getPixel(displayCommon.width - 1, displayCommon.height - 1), 1);
}

void run_tests_common()
{
    RUN_TEST(test_display_size);
    RUN_TEST(test_clear);
    RUN_TEST(test_framebuffer_pixel);
}
