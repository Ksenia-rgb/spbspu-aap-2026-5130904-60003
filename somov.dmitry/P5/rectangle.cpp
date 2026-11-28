#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(double width, double height, point_t pos):
  width_(width),
  height_(height),
  center_(pos)
{
  if ((width_ <= 0) || (height_ <= 0))
  {
    throw std::invalid_argument("ERROR: Incorrect sizes of rectangle!\n");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, {center_.x, center_.y}};
}

void Rectangle::move(const point_t& new_pos)
{
  center_ = new_pos;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("ERROR: Incorrect k!\n");
  }
  width_ = width_ * factor;
  height_ = height_ * factor;
}
