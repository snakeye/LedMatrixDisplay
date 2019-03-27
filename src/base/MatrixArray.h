#pragma once

#include <base/Matrix.h>

namespace LedMatrixDisplay
{

/**
 * @brief Definition of the LED matrix array geometry
 *
 * Multiple matrices are connected in 2D array to build display. This class defines geometry
 * of this array
 *
 * @tparam TMatrix matrix definition
 * @tparam _cols columns
 * @tparam _rows rows
 */
template <class TMatrix, const unsigned int _cols, const unsigned int _rows>
class MatrixArray
{
public:
  //
  static const unsigned int matrixWidth = TMatrix::cols;
  static const unsigned int matrixHeight = TMatrix::rows;

  //
  static const unsigned int arrayCols = _cols;
  static const unsigned int arrayRows = _rows;
  static const unsigned int matrixCount = _cols * _rows;

  // Matrix array dimensions in pixels
  static const unsigned int width = _cols * TMatrix::cols;
  static const unsigned int height = _rows * TMatrix::rows;
};

} // namespace LedMatrixDisplay