#pragma once

#include <Arduino.h>
#include <SPI.h>

#include "Driver.h"

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

namespace LedMatrixDisplay
{

class MAX7219_SPI : Driver
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

}