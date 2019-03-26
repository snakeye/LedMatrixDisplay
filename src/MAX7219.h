#pragma once

#include <LedMatrixDisplay.h>

// max7219 registers
#define MAX7219_REG_NOOP 0x0
#define MAX7219_REG_DIGIT0 0x1
#define MAX7219_REG_DIGIT1 0x2
#define MAX7219_REG_DIGIT2 0x3
#define MAX7219_REG_DIGIT3 0x4
#define MAX7219_REG_DIGIT4 0x5
#define MAX7219_REG_DIGIT5 0x6
#define MAX7219_REG_DIGIT6 0x7
#define MAX7219_REG_DIGIT7 0x8
#define MAX7219_REG_DECODEMODE 0x9
#define MAX7219_REG_INTENSITY 0xA
#define MAX7219_REG_SCANLIMIT 0xB
#define MAX7219_REG_SHUTDOWN 0xC
#define MAX7219_REG_DISPLAYTEST 0xF

namespace LedMatrixDisplay
{

namespace MAX7219
{

template <class LedMatrixArray, class Driver>
class LedMatrixDisplayAbstract : public LedMatrixDisplay<LedMatrixArray>, public Driver
{
public:
  virtual void init() = 0;
  virtual void commit() = 0;

  void setIntensity(const unsigned char intensity)
  {
    Driver::send(MAX7219_REG_INTENSITY, intensity);
  }
};

template <class LedMatrixArray, class Driver>
class LedMatrixDisplayColumnAnode : public LedMatrixDisplayAbstract<LedMatrixArray, Driver>
{
public:
  void init()
  {
    Driver::init(LedMatrixArray::matrixCount);

    Driver::send(MAX7219_REG_DECODEMODE, 0);
    Driver::send(MAX7219_REG_SCANLIMIT, LedMatrixArray::matrixHeight);
    Driver::send(MAX7219_REG_SHUTDOWN, 1);
    Driver::send(MAX7219_REG_DISPLAYTEST, 0);
  }

  void commit()
  {
    // process rows in all matrices
    for (unsigned int row = 0; row < LedMatrixArray::matrixHeight; row++)
    {
      unsigned char registers[LedMatrixArray::matrixCount] = {0};
      unsigned char values[LedMatrixArray::matrixCount] = {0};

      // cycle matrices by columns and rows
      for (unsigned int my = 0; my < LedMatrixArray::arrayRows; my++)
      {
        for (unsigned int mx = 0; mx < LedMatrixArray::arrayCols; mx++)
        {
          // flatten matrix index
          unsigned int matrix = my * LedMatrixArray::arrayCols + mx;

          unsigned char value = 0;
          for (unsigned int col = 0; col < LedMatrixArray::matrixWidth; col++)
          {
            if (this->getPixel(mx * LedMatrixArray::matrixWidth + col, my * LedMatrixArray::matrixHeight + row))
            {
              value |= (1 << col);
            }
          }

          registers[matrix] = MAX7219_REG_DIGIT0 + row;
          values[matrix] = value;
        }
      }

      // send
      Driver::send(&registers[0], &values[0]);
    }
  }
};

template <class LedMatrixArray, class Driver>
class LedMatrixDisplayColumnCathode : public LedMatrixDisplayAbstract<LedMatrixArray, Driver>
{
public:
  void init()
  {
    Driver::init(LedMatrixArray::matrixCount);

    Driver::send(MAX7219_REG_DECODEMODE, 0);
    Driver::send(MAX7219_REG_SCANLIMIT, LedMatrixArray::matrixWidth);
    Driver::send(MAX7219_REG_SHUTDOWN, 1);
    Driver::send(MAX7219_REG_DISPLAYTEST, 0);
  }

  void commit()
  {
    // process rows in all matrices
    for (unsigned int col = 0; col < LedMatrixArray::matrixWidth; col++)
    {
      unsigned char registers[LedMatrixArray::matrixCount] = {0};
      unsigned char values[LedMatrixArray::matrixCount] = {0};

      // cycle matrices by columns and rows
      for (unsigned int my = 0; my < LedMatrixArray::arrayRows; my++)
      {
        for (unsigned int mx = 0; mx < LedMatrixArray::arrayCols; mx++)
        {
          // flatten matrix index
          unsigned int matrix = my * LedMatrixArray::arrayCols + mx;

          unsigned char value = 0;
          for (unsigned int row = 0; row < LedMatrixArray::matrixHeight; row++)
          {
            if (this->getPixel(mx * LedMatrixArray::matrixWidth + col, my * LedMatrixArray::matrixHeight + row))
            {
              value |= (1 << row);
            }
          }

          registers[matrix] = MAX7219_REG_DIGIT0 + col;
          values[matrix] = value;
        }
      }

      // send
      Driver::send(&registers[0], &values[0]);
    }
  }
};

} // namespace MAX7219
} // namespace LedMatrixDisplay
