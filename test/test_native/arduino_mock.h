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

#endif
