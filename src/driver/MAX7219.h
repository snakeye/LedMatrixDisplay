#pragma once

#include <SPI.h>

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

/**
 * @brief
 *
 * @tparam TCanvas
 * @tparam pinCS
 */
template <class TCanvas, const unsigned int pinCS>
class MAX7219_Base : public TCanvas
{
protected:
  const unsigned int driverCount = TCanvas::matrixCount;

public:
  /**
   * @brief Initialize drivers
   *
   */
  void init()
  {
    pinMode(pinCS, OUTPUT);

    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV128);

    send(MAX7219_REG_DECODEMODE, 0);
    send(MAX7219_REG_DISPLAYTEST, 0);
    send(MAX7219_REG_INTENSITY, 0);
    send(MAX7219_REG_SHUTDOWN, 1);
  }

  /**
   * @brief Set brightness intensity
   *
   * @param intensity value in range 0..15
   */
  void setIntensity(const unsigned char intensity)
  {
    send(MAX7219_REG_INTENSITY, intensity);
  }

  /**
   * @brief Update given register on all matrices
   *
   * @param reg
   * @param value
   */
  void send(const unsigned char reg, const unsigned char value)
  {
    unsigned char regs[driverCount];
    unsigned char vals[driverCount];

    for (unsigned int i = 0; i < driverCount; i++)
    {
      regs[i] = reg;
      vals[i] = value;
    }

    send(&regs[0], &vals[0]);
  }

  /**
   * @brief
   *
   * @param matrix
   * @param reg
   * @param value
   */
  void send(const unsigned int matrix, const unsigned char reg, const unsigned char value)
  {
    unsigned char regs[driverCount] = {0};
    unsigned char vals[driverCount] = {0};

    regs[matrix] = reg;
    vals[matrix] = value;

    send(&regs[0], &vals[0]);
  }

  /**
   * @brief
   *
   * @param regs
   * @param values
   */
  void send(const unsigned char *regs, const unsigned char *values)
  {
    // enable the line
    digitalWrite(pinCS, LOW);

    // now shift out the data
    for (unsigned int i = 0; i < driverCount; i++)
    {
      SPI.transfer(regs[driverCount - 1 - i]);
      SPI.transfer(values[driverCount - 1 - i]);
    }

    digitalWrite(pinCS, HIGH);
  }
};

template <class TCanvas, const unsigned int pinCS>
class MAX7219ColumnAnode : public MAX7219_Base<TCanvas, pinCS>
{
  typedef MAX7219_Base<TCanvas, pinCS> TParent;

public:
  /**
   * @brief Initialize drivers
   *
   */
  void init()
  {
    TParent::init();

    TParent::send(MAX7219_REG_SCANLIMIT, TParent::matrixHeight - 1);
  }

  /**
   * @brief Send framebuffer contents to the devices
   *
   */
  void commit()
  {
    // process rows in all matrices
    for (unsigned int row = 0; row < TParent::matrixHeight; row++)
    {
      unsigned char registers[TParent::matrixCount] = {0};
      unsigned char values[TParent::matrixCount] = {0};

      // cycle matrices by columns and rows
      for (unsigned int my = 0; my < TParent::arrayRows; my++)
      {
        for (unsigned int mx = 0; mx < TParent::arrayCols; mx++)
        {
          // flatten matrix index
          unsigned int matrix = my * TParent::arrayCols + mx;

          unsigned char value = 0;
          for (unsigned int col = 0; col < TParent::matrixWidth; col++)
          {
            if (this->getPixel(mx * TParent::matrixWidth + col, my * TParent::matrixHeight + row))
            {
              value |= (1 << col);
            }
          }

          registers[matrix] = MAX7219_REG_DIGIT0 + row;
          values[matrix] = value;
        }
      }

      // send
      TParent::send(&registers[0], &values[0]);
    }
  }
};

/**
 * @brief
 *
 * @tparam TCanvas
 * @tparam pinCS
 */
template <class TCanvas, const unsigned int pinCS>
class MAX7219ColumnCathode : public MAX7219_Base<TCanvas, pinCS>
{
  typedef MAX7219_Base<TCanvas, pinCS> TParent;

public:
  /**
   * @brief Initialize drivers
   *
   */
  void init()
  {
    TParent::init();

    TParent::send(MAX7219_REG_SCANLIMIT, TParent::matrixWidth - 1);
  }

  /**
   * @brief Send framebuffer content to the devices
   *
   */
  void commit()
  {
    // process rows in all matrices
    for (unsigned int col = 0; col < TParent::matrixWidth; col++)
    {
      unsigned char registers[TParent::matrixCount] = {0};
      unsigned char values[TParent::matrixCount] = {0};

      // cycle matrices by columns and rows
      for (unsigned int my = 0; my < TParent::arrayRows; my++)
      {
        for (unsigned int mx = 0; mx < TParent::arrayCols; mx++)
        {
          // flatten matrix index
          unsigned int matrix = my * TParent::arrayCols + mx;

          unsigned char value = 0;
          for (unsigned int row = 0; row < TParent::matrixHeight; row++)
          {
            if (this->getPixel(mx * TParent::matrixWidth + col, my * TParent::matrixHeight + row))
            {
              value |= (1 << row);
            }
          }

          registers[matrix] = MAX7219_REG_DIGIT0 + col;
          values[matrix] = value;
        }
      }

      // send
      TParent::send(&registers[0], &values[0]);
    }
  }
};

} // namespace MAX7219
} // namespace LedMatrixDisplay
