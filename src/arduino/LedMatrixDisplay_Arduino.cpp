#include <Arduino.h>

#include "arduino/LedMatrixDisplay_Arduino.h"

namespace LedMatrixDisplay
{
namespace MAX7219
{
namespace Arduino
{

void MAX7219_SPI::init(const unsigned int _driverCount)
{
}

void MAX7219_SPI::send(const unsigned char reg, const unsigned char value)
{
}

void MAX7219_SPI::send(const unsigned int matrix, const unsigned char reg, const unsigned char value)
{
}

void MAX7219_SPI::send(const unsigned char *reg, const unsigned char *values)
{
}

} // namespace Arduino
} // namespace MAX7219
} // namespace LedMatrixDisplay
