#pragma once

namespace LedMatrixDisplay
{

/**
 * @brief Definition of the single LED matrix geometry
 *
 * @tparam _cols columns
 * @tparam _rows rows
 */
template <const int _cols, const int _rows>
class Matrix
{
public:
  static const int cols = _cols;
  static const int rows = _rows;
};

/**
 * @brief Predefined LED matrix of size 5x7
 */
class Matrix5x7 : public Matrix<5, 7>
{
};

/**
 * @brief Predefined LED matrix of size 8x8
 */
class Matrix8x8 : public Matrix<8, 8>
{
};

} // namespace LedMatrixDisplay