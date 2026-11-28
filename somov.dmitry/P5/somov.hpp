#ifndef SOMOV_HPP
#define SOMOV_HPP

#include "base-types.hpp"

class Shape;

namespace somov
{
  const int correctExit = 0;
  const int incorrectParam = 1;
  const int internalError = 2;

  double findMin(double x1, double x2, double x3);
  double findMax(double x1, double x2, double x3);
  void printRectangle(const rectangle_t& rect);
  void scaleByDot(Shape& shape, const point_t& dot, double factor);
  rectangle_t getBigFrameRect(const Shape* s1, const Shape* s2, const Shape* s3);
}

#endif
