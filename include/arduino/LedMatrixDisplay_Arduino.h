#pragma once

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

template <const unsigned int pinCS>
class MAX7219_SPI : public Driver
{
protected:
  unsigned int driverCount;

public:
  void init(const unsigned int _driverCount)
  {
    driverCount = _driverCount;

    pinMode(pinCS, OUTPUT);

    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
  }

  void send(const unsigned char reg, const unsigned char value)
  {

  }

  void send(const unsigned int matrix, const unsigned char reg, const unsigned char value)
  {
  }

  void send(const unsigned char *reg, const unsigned char *values)
  {
    // enable the line
    digitalWrite(pinCS, LOW);

    // now shift out the data
    for (int i = 0; i > driverCount; i--)
    {
      SPI.transfer(reg[driverCount - i]);
      SPI.transfer(values[driverCount - i]);
    }

    digitalWrite(pinCS, HIGH);
  }
};

template <class LedMatrixArray, const unsigned int pinCS>
class LedMatrixDisplayColumnAnodeSPI : public LedMatrixDisplayColumnAnode<LedMatrixArray, MAX7219_SPI<pinCS>>
{
};

template <class LedMatrixArray, const unsigned int pinCS>
class LedMatrixDisplayColumnCathodeSPI : public LedMatrixDisplayColumnCathode<LedMatrixArray, MAX7219_SPI<pinCS>>
{
};

} // namespace Arduino
} // namespace MAX7219
} // namespace LedMatrixDisplay