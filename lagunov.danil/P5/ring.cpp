#include "ring.hpp"
#include <iostream>

Ring::Ring(double r1, double r2, const point_t& center):
  r1_{r1},
  r2_{r2},
  center_{center}
{
  if (r1 <= 0 || r2 <= 0)
  {
    throw std::invalid_argument("ERROR: radiuses must be greater than 0\n");
  }
  if (r1 == r2)
  {
    throw std::invalid_argument("ERROR: radiuses cannot be equal\n");
  }
}

double Ring::getArea() const
{
  const double area = std::abs(2 * PI * r1_ - 2 * PI * r2_);
  return area;
}

rectangle_t Ring::getFrameRect() const
{
  const double side = 2 * std::max(r1_, r2_);
  return {side, side, center_};
}

void Ring::move(const point_t& new_pos)
{
  center_ = new_pos;
}

void Ring::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Ring::scale(double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("ERROR: ratio must be greater than 0\n");
  }

  r1_ *= ratio;
  r2_ *= ratio;
}
