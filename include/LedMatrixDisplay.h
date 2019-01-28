#pragma once

#include "LedMatrixArray.h"

namespace LedMatrixDisplay
{

template <class LedMatrixArray>
class LedMatrixDisplay : public LedMatrixArray
{
protected:
  static const unsigned int frameBufferSize = LedMatrixArray::width * LedMatrixArray::arrayRows;

protected:
  byte frameBuffer[frameBufferSize] = {0};

public:
  void clear()
  {
    for (int i = 0; i < frameBufferSize; i++)
    {
      frameBuffer[i] = 0;
    }
  }

  void setPixel(int x, int y)
  {
    unsigned int row = y / LedMatrixArray::matrixHeight;
    unsigned int bit = y % LedMatrixArray::matrixHeight;

    frameBuffer[LedMatrixArray::width * row + x] |= (1 << bit);
  }

  void clearPixel(int x, int y)
  {
    unsigned int row = y / LedMatrixArray::matrixHeight;
    unsigned int bit = y % LedMatrixArray::matrixHeight;

    frameBuffer[LedMatrixArray::width * row + x] &= ~(1 << bit);
  }

  bool getPixel(int x, int y)
  {
    unsigned int row = y / LedMatrixArray::matrixHeight;
    unsigned int bit = y % LedMatrixArray::matrixHeight;

    return ((frameBuffer[LedMatrixArray::width * row + x] >> bit) & 1) != 0;
  }
};

} // namespace LedMatrixDisplay
