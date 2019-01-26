#pragma once

// #include <Arduino.h>
// #include <SPI.h>

#include "font.h"

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

#define TEXT_ALIGN_LEFT 0      // Text is aligned to left side of the display
#define TEXT_ALIGN_LEFT_END 1  // Beginning of text is just outside the right end of the display
#define TEXT_ALIGN_RIGHT 2     // End of text is aligned to the right of the display
#define TEXT_ALIGN_RIGHT_END 3 // End of text is just outside the left side of the display
#define TEXT_ALIGN_CENTER 4    // center

namespace MAX7219
{

template <const int _rows, const int _cols>
class LedMatrixCommonAnode
{
protected:
public:
  static const int rows = _rows;
  static const int cols = _cols;
};

template <const int _rows, const int _cols>
class LedMatrixCommonCathode
{
protected:
public:
  static const int rows = _rows;
  static const int cols = _cols;
};

class LedMatrixCommonAnodeSquare : public LedMatrixCommonAnode<8, 8>
{
};

class LedMatrixCommonCathodeSquare : public LedMatrixCommonCathode<8, 8>
{
};

class MAX7219_SPI
{
public:
  unsigned int pinCS;

public:
  void init()
  {
  }

  void sendByte(const byte reg, const byte data)
  {
  }
};

class MAX7219_Mock
{
public:
  void init()
  {
  }

  void sendByte(const byte a, const byte b, const byte c)
  {
  }

  void sendByte(const byte reg, const byte data)
  {
    registers[reg] = data;
  }

  void sendBytes(const byte *reg, const byte *data)
  {
  }

public:
  byte checkRegister(const byte reg)
  {
    return registers[reg];
  }

protected:
  byte registers[16] = {0};
};

/**
 * Main display class
 */
template <class MatrixType, const unsigned int _width, const unsigned int _height, class TConn>
class LedMatrixDisplay : public TConn
{
protected:
  static const unsigned int matrixCount = _width * _height;

  byte frameBuffer[_width * MatrixType::cols * _height] = {0};

public:
  LedMatrixDisplay()
  {
  }

public:
  void init()
  {
    TConn::init();

    for (int device = 0; device < matrixCount; device++)
    {
      TConn::sendByte(device, MAX7219_REG_SCANLIMIT, 7);   // show all 8 digits
      TConn::sendByte(device, MAX7219_REG_DECODEMODE, 0);  // using an led matrix (not digits)
      TConn::sendByte(device, MAX7219_REG_DISPLAYTEST, 0); // no display test
      TConn::sendByte(device, MAX7219_REG_INTENSITY, 0);   // character intensity: range: 0 to 15
      TConn::sendByte(device, MAX7219_REG_SHUTDOWN, 1);    // not in shutdown mode (ie. start it up)
    }
  }

public:
  /**
   * Display width in pixels
   */
  unsigned int width()
  {
    return _width * MatrixType::cols;
  }

  /**
   * Display height in pixels
   */
  unsigned int height()
  {
    return _height * MatrixType::rows;
  }

public:
  void setIntensity(const byte intensity)
  {
    TConn::sendByte(MAX7219_REG_INTENSITY, intensity);
  }

public:
  /**
   *  Clear the frame buffer.
   */
  void clear()
  {
    for (int col = 0; col < _width * MatrixType::cols * _height; col++)
    {
      frameBuffer[col] = 0;
    }
  }

  /**
   *  Writes the frame buffer to the displays.
   */
  void commit()
  {
    byte reg[matrixCount] = {0};
    byte data[matrixCount] = {0};

    for (int row = 0; row < 8; row++)
    {
      for (int i = 0; i < matrixCount; i++)
      {
        // register value
        reg[i] = row + 1;

        // data value
        for (int col = 0; col < 8; col++)
        {
          byte pixel = getPixel(i * 8 + col, 8 - row - 1);
          bitWrite(data[i], col, pixel);
        }
      }

      TConn::sendBytes(reg, data);
    }
  }

public:
  /**
   * Turn on pixel at position (x, y).
   */
  void setPixel(unsigned int x, unsigned int y)
  {
    bitWrite(frameBuffer[x], y, true);
  }

  /**
   * Clear pixel
   */
  void clearPixel(unsigned int x, unsigned int y)
  {
    bitWrite(frameBuffer[x], y, false);
  }

  /**
   * Get pixel value at position (x, y)
   */
  bool getPixel(unsigned int x, unsigned int y)
  {
    return bitRead(frameBuffer[x], y);
  }
};

} // namespace MAX7219
