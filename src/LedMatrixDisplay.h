#pragma once

#include <base/Canvas.h>
#include <driver/MAX7219.h>

namespace LedMatrixDisplay
{

template <class Canvas, const unsigned int pinCS>
class DisplayColumnAnode : public MAX7219::MAX7219ColumnAnode<Canvas, pinCS>
{
};

template <class Canvas, const unsigned int pinCS>
class DisplayColumnCathode : public MAX7219::MAX7219ColumnCathode<Canvas, pinCS>
{
};

} // namespace LedMatrixDisplay