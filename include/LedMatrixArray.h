#pragma once

#include <LedMatrix.h>

namespace LedMatrixDisplay
{

/**
 * Definition of LED matrix array
 */
template <class LedMatrixType, const unsigned int _cols, const unsigned int _rows>
class LedMatrixArray
{
public:
  //
  static const unsigned int matrixCols = LedMatrixType::cols;
  static const unsigned int matrixRows = LedMatrixType::rows;

  //
  static const unsigned int arrayCols = _cols;
  static const unsigned int arrayRows = _rows;
  static const unsigned int matrixCount = _cols * _rows;

  // Matrix array dimensions in pixels
  static const unsigned int width = _cols * LedMatrixType::cols;
  static const unsigned int height = _rows * LedMatrixType::rows;
};

}