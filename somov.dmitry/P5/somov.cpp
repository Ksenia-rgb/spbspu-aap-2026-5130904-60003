#include "somov.hpp"
#include "shape.hpp"
#include <iostream>
#include <stdexcept>

double somov::findMin(double x1, double x2, double x3)
{
  double result = x1;
  if (x2 < result)
  {
    result = x2;
  }
  if (x3 < result)
  {
    result = x3;
  }
  return result;
}

double somov::findMax(double x1, double x2, double x3)
{
  double result = x1;
  if (x2 > result)
  {
    result = x2;
  }
  if (x3 > result)
  {
    result = x3;
  }
  return result;
}

void somov::printRectangle(const rectangle_t& rect)
{
  std::cout << rect.width << " ";
  std::cout << rect.height << " ";
  std::cout << rect.pos.x << " ";
  std::cout << rect.pos.y << "\n";
}

void somov::scaleByDot(Shape& shape, const point_t& dot, double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("ERROR: Incorrect factor!");
  }
  const point_t oldPos = shape.getFrameRect().pos;
  shape.move(dot);
  shape.scale(factor);

  const double dx = factor * (oldPos.x - dot.x);
  const double dy = factor * (oldPos.y - dot.y);
  shape.move(dx, dy);
}

rectangle_t somov::getBigFrameRect(const Shape* s1, const Shape* s2, const Shape* s3)
{
  const double half = 0.5;
  const rectangle_t f1 = s1->getFrameRect();
  const rectangle_t f2 = s2->getFrameRect();
  const rectangle_t f3 = s3->getFrameRect();

  const double x1_min = f1.pos.x - (f1.width * half);
  const double x2_min = f2.pos.x - (f2.width * half);
  const double x3_min = f3.pos.x - (f3.width * half);
  const double min_x = findMin(x1_min, x2_min, x3_min);

  const double x1_max = f1.pos.x + (f1.width * half);
  const double x2_max = f2.pos.x + (f2.width * half);
  const double x3_max = f3.pos.x + (f3.width * half);
  const double max_x = findMax(x1_max, x2_max, x3_max);

  const double y1_min = f1.pos.y - (f1.height * half);
  const double y2_min = f2.pos.y - (f2.height * half);
  const double y3_min = f3.pos.y - (f3.height * half);
  const double min_y = findMin(y1_min, y2_min, y3_min);

  const double y1_max = f1.pos.y + (f1.height * half);
  const double y2_max = f2.pos.y + (f2.height * half);
  const double y3_max = f3.pos.y + (f3.height * half);
  const double max_y = findMax(y1_max, y2_max, y3_max);

  const double width = max_x - min_x;
  const double height = max_y - min_y;
  return {width, height, {min_x + (width * half), min_y + (height * half)}};
}
