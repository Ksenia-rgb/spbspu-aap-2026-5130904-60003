#include "rectangle.hpp"

#include <cmath>
#include <stdexcept>

namespace
{
  void validateFinitePosition(const ognovenko::point_t& pos)
  {
    if (!std::isfinite(pos.x) || !std::isfinite(pos.y))
    {
      throw std::invalid_argument("Rectangle position must be finite");
    }
  }

  void validatePositiveFinite(double value, const char* message)
  {
    if (!std::isfinite(value) || value <= 0.0)
    {
      throw std::invalid_argument(message);
    }
  }
}

ognovenko::Rectangle::Rectangle(const ognovenko::point_t& pos, double width, double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  validateFinitePosition(pos_);
  validatePositiveFinite(width_, "Rectangle width must be positive and finite");
  validatePositiveFinite(height_, "Rectangle height must be positive and finite");
}

double ognovenko::Rectangle::getArea() const
{
  return width_ * height_;
}

ognovenko::rectangle_t ognovenko::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void ognovenko::Rectangle::move(const ognovenko::point_t& pos)
{
  validateFinitePosition(pos);
  pos_ = pos;
}

void ognovenko::Rectangle::move(double dx, double dy)
{
  const ognovenko::point_t new_pos = {pos_.x + dx, pos_.y + dy};
  validateFinitePosition(new_pos);
  pos_ = new_pos;
}

void ognovenko::Rectangle::scale(double factor)
{
  validatePositiveFinite(factor, "Scale factor must be positive and finite");
  const double new_width = width_ * factor;
  const double new_height = height_ * factor;
  validatePositiveFinite(new_width, "Scaled rectangle width is out of range");
  validatePositiveFinite(new_height, "Scaled rectangle height is out of range");
  width_ = new_width;
  height_ = new_height;
}
