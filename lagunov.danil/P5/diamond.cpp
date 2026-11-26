#include "diamond.hpp"
#include <iostream>

Diamond::Diamond(double d1, double d2, const point_t& center):
  d1_{d1},
  d2_{d2},
  center_{center}
{
  if (d1 <= 0 || d2 <= 0)
  {
    throw std::invalid_argument("ERROR: diagonals must be greater than 0\n");
  }
}

double Diamond::getArea() const
{
  const double area = d1_ * d2_ / 2.0;
  return area;
}

rectangle_t Diamond::getFrameRect() const
{
  return {d1_, d2_, center_};
}

void Diamond::move(const point_t& new_pos)
{
  center_ = new_pos;
}

void Diamond::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Diamond::scale(double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("ERROR: ratio must be greater than 0\n");
  }

  d1_ *= ratio;
  d2_ *= ratio;
}
