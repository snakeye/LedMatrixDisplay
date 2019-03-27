#pragma once

namespace LedMatrixDisplay
{

/**
 * @brief Definition of the single LED matrix geometry
 *
 * Single matrix is 2D array of LED pixels. This class defines geometry of this array
 *
 * @tparam _cols columns
 * @tparam _rows rows
 */
template <const int _cols, const int _rows>
class Matrix
{
public:
  /**
   * @brief number of columns in matrix
   *
   */
  static const int cols = _cols;

  /**
   * @brief number of rows in matrix
   *
   */
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