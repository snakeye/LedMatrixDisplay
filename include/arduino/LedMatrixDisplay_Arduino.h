#pragma once

#include <Arduino.h>
#include <SPI.h>

#include "Driver.h"

#define TEXT_ALIGN_LEFT 0      // Text is aligned to left side of the display
#define TEXT_ALIGN_LEFT_END 1  // Beginning of text is just outside the right end of the display
#define TEXT_ALIGN_RIGHT 2     // End of text is aligned to the right of the display
#define TEXT_ALIGN_RIGHT_END 3 // End of text is just outside the left side of the display
#define TEXT_ALIGN_CENTER 4    // center

namespace LedMatrixDisplay
{

class MAX7219_SPI : public Driver
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

} // namespace LedMatrixDisplay