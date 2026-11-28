#include "xquare.hpp"

#include <cmath>
#include <stdexcept>

namespace
{
  void validateFinitePosition(const ognovenko::point_t& pos)
  {
    if (!std::isfinite(pos.x) || !std::isfinite(pos.y))
    {
      throw std::invalid_argument("Xquare position must be finite");
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

ognovenko::Xquare::Xquare(const ognovenko::point_t& pos, double diagonal):
  pos_(pos),
  diagonal_(diagonal)
{
  validateFinitePosition(pos_);
  validatePositiveFinite(diagonal_, "Xquare diagonal must be positive and finite");
}

double ognovenko::Xquare::getArea() const
{
  constexpr double area_divisor = 2.0;
  return (diagonal_ * diagonal_) / area_divisor;
}

ognovenko::rectangle_t ognovenko::Xquare::getFrameRect() const
{
  return {diagonal_, diagonal_, pos_};
}

void ognovenko::Xquare::move(const ognovenko::point_t& pos)
{
  validateFinitePosition(pos);
  pos_ = pos;
}

void ognovenko::Xquare::move(double dx, double dy)
{
  const ognovenko::point_t new_pos = {pos_.x + dx, pos_.y + dy};
  validateFinitePosition(new_pos);
  pos_ = new_pos;
}

void ognovenko::Xquare::scale(double factor)
{
  validatePositiveFinite(factor, "Scale factor must be positive and finite");
  const double new_diagonal = diagonal_ * factor;
  validatePositiveFinite(new_diagonal, "Scaled Xquare diagonal is out of range");
  diagonal_ = new_diagonal;
}
