#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
typedef unsigned char byte;

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

class MAX7219_Mock
{
public:
  MAX7219_Mock()
  {
    driverCount = 0;
    registers = NULL;
  }

  ~MAX7219_Mock()
  {
    if (registers != NULL)
    {
      delete[] registers;
    }
  }

  void init(const unsigned int matrixCount)
  {
    driverCount = matrixCount;
    registers = new byte[driverCount * 16];
  }

  void sendByte(const unsigned int matrix, const byte reg, const byte value)
  {
    registers[matrix * driverCount + reg] = value;
  }

public:
  byte checkRegister(const unsigned int matrix, const byte reg)
  {
    return registers[matrix * driverCount + reg];
  }

protected:
  unsigned int driverCount;
  byte *registers;
};

#endif
