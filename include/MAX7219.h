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

  void setIntensity(const unsigned int intensity)
  {
  }
};

template <class LedMatrixArray, class Driver>
class LedMatrixDisplayCommonAnode : public LedMatrixDisplayAbstract<LedMatrixArray, Driver>
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
class LedMatrixDisplayCommonCathode : public LedMatrixDisplayAbstract<LedMatrixArray, Driver>
{
public:
  void init()
  {
  }

  void commit()
  {
  }
};

} // namespace MAX7219
} // namespace LedMatrixDisplay
