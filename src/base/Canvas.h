#pragma once

#include "base/MatrixArray.h"

namespace LedMatrixDisplay
{

/**
 * @brief Test alignment
 *
 */
enum TextAlign
{
  left,
  leftEnd,
  right,
  rightEnd,
  center
};

/**
 * @brief Canvas objct providing basic graphics operations
 *
 * @tparam TMatrixArray defines geometry of the matrix array
 */
template <class TMatrixArray>
class Canvas : public TMatrixArray
{
protected:
  static const unsigned int frameBufferSize = TMatrixArray::width * TMatrixArray::arrayRows;

protected:
  unsigned char frameBuffer[frameBufferSize] = {0};

public:
  /**
   * @brief Clear the canvas
   *
   * Set all pixels to zero
   */
  void clear()
  {
    for (int i = 0; i < frameBufferSize; i++)
    {
      frameBuffer[i] = 0;
    }
  }

  /**
   * @brief Set single pixel
   *
   * @param x
   * @param y
   */
  void setPixel(int x, int y)
  {
    unsigned int row = y / TMatrixArray::matrixHeight;
    unsigned int bit = y % TMatrixArray::matrixHeight;

    frameBuffer[TMatrixArray::width * row + x] |= (1 << bit);
  }

  /**
   * @brief Clear single pixel
   *
   * @param x
   * @param y
   */
  void clearPixel(int x, int y)
  {
    unsigned int row = y / TMatrixArray::matrixHeight;
    unsigned int bit = y % TMatrixArray::matrixHeight;

    frameBuffer[TMatrixArray::width * row + x] &= ~(1 << bit);
  }

  /**
   * @brief Get current pixel value in the framebuffer
   *
   * @param x
   * @param y
   * @return true
   * @return false
   */
  bool getPixel(int x, int y)
  {
    unsigned int row = y / TMatrixArray::matrixHeight;
    unsigned int bit = y % TMatrixArray::matrixHeight;

    return ((frameBuffer[TMatrixArray::width * row + x] >> bit) & 1) != 0;
  }
};

} // namespace LedMatrixDisplay
