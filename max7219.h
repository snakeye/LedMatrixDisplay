#pragma once

#include <Arduino.h>

class MAX7219_Driver
{

};

class MAX7219_Driver_CommonAnode : MAX7219_Driver
{

};

class MAX7219_Driver_CommonCathode : MAX7219_Driver
{

};

template <class Driver>
class MAX7219_Display : Driver
{
  public:
    MAX7219_Display();

    void init();

    void setBrightness(int brightness);

    void clear();

    void setPixel(int x, int y);

    void drawChar(char ch, int x, int y);


    void setText(String text);

    void drawText();

    void commit();

  protected:

};



