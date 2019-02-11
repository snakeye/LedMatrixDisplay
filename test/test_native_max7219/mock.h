#pragma once

#include <vector>

class MAX7219_Mock
{
public:
  void init(const unsigned int _driverCount)
  {
    driverCount = _driverCount;
    registers.resize(_driverCount * 16);
  }

  // send the same data to all drivers
  void send(const unsigned char reg, const unsigned char value)
  {
    for (unsigned int matrix = 0; matrix < driverCount; matrix++)
    {
      registers[matrix * driverCount + reg] = value;
    }
  }

  // send the value to the given matrix
  void send(const unsigned int matrix, const unsigned char reg, const unsigned char value)
  {
    std::vector<unsigned char> registers(driverCount);
    registers[matrix] = reg;

    std::vector<unsigned char> values(driverCount);
    values[matrix] = value;

    send(&registers[0], &values[0]);
  }

  // send values to the given matrix
  void send(const unsigned char *reg, const unsigned char *values)
  {
    for (unsigned int matrix = 0; matrix < driverCount; matrix++)
    {
      registers[matrix * driverCount + reg[matrix]] = values[matrix];
    }
  }

public:
  unsigned char checkRegister(const unsigned int matrix, const unsigned char reg)
  {
    return registers[matrix * driverCount + reg];
  }

protected:
  unsigned int driverCount;
  std::vector<unsigned char> registers;
};
