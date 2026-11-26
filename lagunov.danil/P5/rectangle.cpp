#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(double width, double height, const point_t& center):
  rect_{width, height, center}
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("ERROR: size must be greater than 0\n");
  }
}

double Rectangle::getArea() const
{
  const double area = rect_.width * rect_.height;
  return area;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t& new_pos)
{
  rect_.pos = new_pos;
}

void Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void Rectangle::scale(double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("ERROR: ratio must be greater than 0\n");
  }

  rect_.width *= ratio;
  rect_.height *= ratio;
}
