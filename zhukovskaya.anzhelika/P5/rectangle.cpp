#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(double width, double height, const point_t &center):
  rect_{width, height, center}
{
  if (width <= 0.0 || height <= 0.0)
  {
    throw std::invalid_argument("arguments must be > 0");
  }
}

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}
rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(point_t &new_place)
 {
  rect_.pos = new_place;
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
    throw std::invalid_argument("the ratio must be >0");
  }
  rect_.width *= ratio;
  rect_.height *= ratio;
}
