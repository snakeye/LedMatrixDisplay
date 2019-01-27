#pragma once

#include "LedMatrixArray.h"

namespace LedMatrixDisplay
{

template <class LedMatrixArray>
class LedMatrixDisplay : public LedMatrixArray
{
protected:
  static const unsigned int frameBufferSize = LedMatrixArray::width * LedMatrixArray::matrixRows;

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
    unsigned int row = y / LedMatrixArray::matrixRows;
    unsigned int bit = y % LedMatrixArray::matrixRows;
    
    frameBuffer[x * row] |= (1 << bit);
  }

  void clearPixel(int x, int y)
  {
  }

  bool getPixel(int x, int y)
  {
    unsigned int row = y / LedMatrixArray::matrixRows;
    unsigned int bit = y % LedMatrixArray::matrixRows;

    return frameBuffer[x * row] & (1 << bit) != 0;
  }
};

template <class LedMatrixArray, class Driver>
class LedMatrixDisplayCommonAnode : LedMatrixDisplay<LedMatrixArray>
{
public:
  void init()
  {
  }

  void commit()
  {
  }
};

template <class LedMatrixArray, class Driver>
class LedMatrixDisplayCommonCathode : LedMatrixDisplay<LedMatrixArray>
{
public:
  void init()
  {
  }

  void commit()
  {
  }
};

} 