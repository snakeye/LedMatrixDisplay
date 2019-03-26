#pragma once

namespace LedMatrixDisplay
{

/**
 * Definition of the LED matrix geometry
 */
template <const int _cols, const int _rows>
class LedMatrix
{
public:
  static const int cols = _cols;
  static const int rows = _rows;
};

class LedMatrix5x7 : public LedMatrix<5, 7>
{
};

class LedMatrix8x8 : public LedMatrix<8, 8>
{
};

} // namespace LedMatrixDisplay