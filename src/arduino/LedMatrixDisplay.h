#pragma once

#include <SPI.h>

#include "Driver.h"
#include "MAX7219.h"

#define TEXT_ALIGN_LEFT 0      // Text is aligned to left side of the display
#define TEXT_ALIGN_LEFT_END 1  // Beginning of text is just outside the right end of the display
#define TEXT_ALIGN_RIGHT 2     // End of text is aligned to the right of the display
#define TEXT_ALIGN_RIGHT_END 3 // End of text is just outside the left side of the display
#define TEXT_ALIGN_CENTER 4    // center

namespace LedMatrixDisplay
{
namespace MAX7219
{
namespace Arduino
{

template <const unsigned int _driverCount, const unsigned int pinCS>
class MAX7219_SPI : public Driver
{
protected:
  const unsigned int driverCount = driverCount;

public:
  void init(const unsigned int _)
  {
    pinMode(pinCS, OUTPUT);

    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
  }

  void send(const unsigned char reg, const unsigned char value)
  {
    unsigned char regs[driverCount];
    unsigned char vals[driverCount];

    for(unsigned int i = 0; i < driverCount; i++) {
      regs[i] = reg;
      vals[i] = value;
    }

    send(&regs[0], &vals[0]);
  }

  void send(const unsigned int matrix, const unsigned char reg, const unsigned char value)
  {
    unsigned char regs[driverCount] = {0};
    unsigned char vals[driverCount] = {0};

    regs[matrix] = reg;
    vals[matrix] = value;

    send(&regs[0], &vals[0]);
  }

  void send(const unsigned char *regs, const unsigned char *values)
  {
    // enable the line
    digitalWrite(pinCS, LOW);

    // now shift out the data
    for (unsigned int i = 0; i < driverCount; i++)
    {
      SPI.transfer(regs[driverCount - i - 1]);
      SPI.transfer(values[driverCount - i - 1]);
    }

    digitalWrite(pinCS, HIGH);
  }
};

template <class LedMatrixArray, const unsigned int pinCS>
class LedMatrixDisplayColumnAnodeSPI : public LedMatrixDisplayColumnAnode<LedMatrixArray, MAX7219_SPI<LedMatrixArray::matrixCount, pinCS>>
{
};

template <class LedMatrixArray, const unsigned int pinCS>
class LedMatrixDisplayColumnCathodeSPI : public LedMatrixDisplayColumnCathode<LedMatrixArray, MAX7219_SPI<LedMatrixArray::matrixCount, pinCS>>
{
};

} // namespace Arduino
} // namespace MAX7219
} // namespace LedMatrixDisplay