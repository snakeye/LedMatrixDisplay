#pragma once

#include <Arduino.h>
#include <SPI.h>

// max7219 registers
#define MAX7219_REG_NOOP         0x0
#define MAX7219_REG_DIGIT0       0x1
#define MAX7219_REG_DIGIT1       0x2
#define MAX7219_REG_DIGIT2       0x3
#define MAX7219_REG_DIGIT3       0x4
#define MAX7219_REG_DIGIT4       0x5
#define MAX7219_REG_DIGIT5       0x6
#define MAX7219_REG_DIGIT6       0x7
#define MAX7219_REG_DIGIT7       0x8
#define MAX7219_REG_DECODEMODE   0x9
#define MAX7219_REG_INTENSITY    0xA
#define MAX7219_REG_SCANLIMIT    0xB
#define MAX7219_REG_SHUTDOWN     0xC
#define MAX7219_REG_DISPLAYTEST  0xF

template <int CS_Pin, int Count, class Font>
class MAX7219_Display
{
  private:
    // display data
    byte display[Count * 8] = {0};

    // update buffer
    byte buffer[Count * 8] = {0};

  public:
    MAX7219_Display()
    {

    }

    void init()
    {
      pinMode(CS_Pin, OUTPUT);

      SPI.begin ();
      SPI.setDataMode(SPI_MODE0);
      SPI.setClockDivider(SPI_CLOCK_DIV128);

      for (int device = 0; device < Count; device++) {
        sendByte(device, MAX7219_REG_SCANLIMIT, 7);   // show all 8 digits
        sendByte(device, MAX7219_REG_DECODEMODE, 0);  // using an led matrix (not digits)
        sendByte(device, MAX7219_REG_DISPLAYTEST, 0); // no display test
        sendByte(device, MAX7219_REG_INTENSITY, 0);   // character intensity: range: 0 to 15
        sendByte(device, MAX7219_REG_SHUTDOWN, 1);    // not in shutdown mode (ie. start it up)
      }
    }

    void setBrightness(int brightness)
    {
      sendByte(MAX7219_REG_INTENSITY, brightness);
    }

    /**
     * Clear display buffer
     */
    void clear()
    {
      for (int i = 0; i < Count * 8; i++) {
        buffer[i] = 0;
      }
    }

    /**
     * Set single pixel
     */
    void setPixel(int x, int y)
    {
      bitWrite(buffer[x], y, true);
    }

    /**
     * Draw single character
     */
    void drawChar(char ch, int x, int y)
    {

    }

    void setText(String text)
    {

    }

    void drawText()
    {

    }

    /**
     * Copy updates from buffer to display and send them to devices
     */
    void commit()
    {
      for (int col = 0; col < Count * 8; col++) {
        sendByte(col / 8, col % 8 + 1, buffer[col]);
      }
    }

  protected:
    void sendByte(const int device, const byte reg, const byte data)
    {
      byte spidata[Count] = {0};
      byte spiregister[Count] = {0};

      // put our device data into the array
      spiregister[device] = reg;
      spidata[device] = data;

      // enable the line
      digitalWrite(CS_Pin, LOW);

      // now shift out the data
      for (int i = 0; i < Count; i++) {
        SPI.transfer (spiregister[i]);
        SPI.transfer (spidata[i]);
      }

      digitalWrite (CS_Pin, HIGH);
    }

    void sendByte (const byte reg, const byte data)
    {
      // enable the line
      digitalWrite(CS_Pin, LOW);

      for (int device = 0; device < Count; device++)
      {
        SPI.transfer (reg);
        SPI.transfer (data);
      }

      digitalWrite (CS_Pin, HIGH);
    }
};



