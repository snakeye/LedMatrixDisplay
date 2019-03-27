#pragma once

#include <base/Canvas.h>
#include <driver/MAX7219.h>

namespace LedMatrixDisplay
{

/**
 * @brief Column Anode MAX7219 LED Matrix
 *
 * LED Matrix display with Column Anode connections driven by MAX7219 drivers
 *
 * @tparam TCanvas canvas definition
 * @tparam pinCS CS pin
 */
template <class TCanvas, const unsigned int pinCS>
class DisplayColumnAnode : public MAX7219::MAX7219ColumnAnode<TCanvas, pinCS>
{
};

/**
 * @brief Column Cathode MAX7219 LED Matrix
 *
 * LED Matrix display with Column Cathode connections driven by MAX7219 drivers
 *
 * @tparam TCanvas
 * @tparam pinCS
 */
template <class TCanvas, const unsigned int pinCS>
class DisplayColumnCathode : public MAX7219::MAX7219ColumnCathode<TCanvas, pinCS>
{
};

} // namespace LedMatrixDisplay