#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <vector>

typedef unsigned char byte;

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

class MAX7219_Mock
{
public:
  void init(const unsigned int _driverCount)
  {
    driverCount = _driverCount;
    registers.resize(_driverCount * 16);
  }

  // send the same data to all drivers
  void send(const byte reg, const byte value)
  {
    for (unsigned int matrix = 0; matrix < driverCount; matrix++)
    {
      registers[matrix * driverCount + reg] = value;
    }
  }

  // send the value to the given matrix
  void send(const unsigned int matrix, const byte reg, const byte value)
  {
    std::vector<byte> registers(driverCount);
    registers[matrix] = reg;

    std::vector<byte> values(driverCount);
    values[matrix] = value;

    send(&registers[0], &values[0]);
  }

  // send values to the given matrix
  void send(const byte *reg, const byte *values)
  {
    for (unsigned int matrix = 0; matrix < driverCount; matrix++)
    {
      registers[matrix * driverCount + reg[matrix]] = values[matrix];
    }
  }

public:
  byte checkRegister(const unsigned int matrix, const byte reg)
  {
    return registers[matrix * driverCount + reg];
  }

protected:
  unsigned int driverCount;
  std::vector<byte> registers;
};

#endif
