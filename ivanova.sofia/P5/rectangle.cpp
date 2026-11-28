#include "rectangle.hpp"
#include<stdexcept>

Rectangle::Rectangle(double width, double height, const point_t& pos)
{
  width_ = width;
  height_ = height;
  pos_ = pos;

  if (width_ <= 0.0 || height_ <= 0.0)
  {
    throw std::invalid_argument("Invalid rectangle parametrs");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void Rectangle::move(const point_t& newPos)
{
  pos_ = newPos;
}

void Rectangle::move(const double delta_x, const double delta_y)
{
  pos_.x_ += delta_x;
  pos_.y_ += delta_y;
}

void Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }
  width_ *= factor;
  height_ *= factor;
}
