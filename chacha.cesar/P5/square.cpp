#include "square.hpp"
#include <stdexcept>

namespace chacha
{
  const double half = 0.5;

  Square::Square(double side, const point_t& bottom_left):
    side_(side)
  {
    if (side <= 0)
    {
      throw std::invalid_argument("Side must be positive");
    }
    center_.x = bottom_left.x + side_ * half;
    center_.y = bottom_left.y + side_ * half;
  }

  double Square::getArea() const
  {
    return side_ * side_;
  }

  rectangle_t Square::getFrameRect() const
  {
    return {side_, side_, center_};
  }

  void Square::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Square::move(const point_t& new_pos)
  {
    center_ = new_pos;
  }
}
