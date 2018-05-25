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

    /**
       Init display
    */
    void init()
    {
      // set Chip Select pin mode
      pinMode(CS_Pin, OUTPUT);

      // init SPI
      SPI.begin ();
      SPI.setDataMode(SPI_MODE0);
      SPI.setClockDivider(SPI_CLOCK_DIV128);

      // init all devices
      for (int device = 0; device < Count; device++) {
        sendByte(device, MAX7219_REG_SCANLIMIT, 7);   // show all 8 digits
        sendByte(device, MAX7219_REG_DECODEMODE, 0);  // using an led matrix (not digits)
        sendByte(device, MAX7219_REG_DISPLAYTEST, 0); // no display test
        sendByte(device, MAX7219_REG_INTENSITY, 0);   // character intensity: range: 0 to 15
        sendByte(device, MAX7219_REG_SHUTDOWN, 1);    // not in shutdown mode (ie. start it up)
      }
    }

    /**
       Set display brightness in range 0..15
    */
    void setBrightness(int brightness)
    {
      sendByte(MAX7219_REG_INTENSITY, brightness);
    }

    /**
       Clear display buffer
    */
    void clear()
    {
      for (int i = 0; i < Count * 8; i++) {
        buffer[i] = 0;
      }
    }

    /**
       Set single pixel
    */
    void setPixel(int x, int y)
    {
      bitWrite(buffer[x], y, true);
    }

    /**
       Draw single character
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
       Copy updates from buffer to display and send them to devices

       @move: low level driver
    */
    void commit()
    {
      byte updates[8][Count] = {0};
      bool pending[8] = {0};

      // collect updates
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < Count; j++) {
          int k = j * 8 + i;

          // check if we need to update display here
          if (display[k] != buffer[k]) {
            updates[i][j] = buffer[k];
            pending[i] = true;
            display[k] = buffer[k];
          }
        }
      }

      // send pending updates to the devices
      for (byte i = 0; i < 8; i++) {
        if (pending[i]) {
          const byte v = i + 1;
          byte reg[Count] = {v};
          sendBytes(reg, updates[i]);
        }
      }
    }

  protected:
    /**
       Send single byte to single device.
       All other devices will be ignored
    */
    void sendByte(const int device, const byte reg, const byte data)
    {
      byte spidata[Count] = {0};
      byte spiregister[Count] = {0};

      // put our device data into the array
      spiregister[device] = reg;
      spidata[device] = data;

      sendBytes(spiregister, spidata);
    }

    /**
       Send single byte to all devices
    */
    void sendByte(const byte reg, const byte data)
    {
      byte r[Count] = {reg};
      byte d[Count] = {data};

      sendBytes(r, d);
    }

    /**
       Send multiple bytes to all devices
    */
    void sendBytes(const byte reg[], const byte data[])
    {
      // enable the line
      digitalWrite(CS_Pin, LOW);

      for (int device = 0; device < Count; device++)
      {
        SPI.transfer (reg[device]);
        SPI.transfer (data[device]);
      }

      digitalWrite (CS_Pin, HIGH);
    }
};



