#include "rubber.hpp"

#include <cmath>
#include <stdexcept>

namespace
{
  void validateFinitePosition(const ognovenko::point_t& pos)
  {
    if (!std::isfinite(pos.x) || !std::isfinite(pos.y))
    {
      throw std::invalid_argument("Rubber position must be finite");
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

ognovenko::Rubber::Rubber(const ognovenko::point_t& outer_pos, double outer_radius,
    const ognovenko::point_t& inner_pos, double inner_radius):
  outer_pos_(outer_pos),
  outer_radius_(outer_radius),
  inner_pos_(inner_pos),
  inner_radius_(inner_radius)
{
  validateFinitePosition(outer_pos_);
  validateFinitePosition(inner_pos_);
  validatePositiveFinite(outer_radius_, "Rubber outer radius must be positive and finite");
  validatePositiveFinite(inner_radius_, "Rubber inner radius must be positive and finite");
  const double distance = std::hypot(outer_pos_.x - inner_pos_.x,
      outer_pos_.y - inner_pos_.y);
  if (!std::isfinite(distance) || distance == 0.0 ||
      (distance + inner_radius_) >= outer_radius_)
  {
    throw std::invalid_argument("Rubber inner circle must be inside and not concentric");
  }
}

double ognovenko::Rubber::getArea() const
{
  constexpr double pi = 3.14159265358979323846;
  return pi * ((outer_radius_ * outer_radius_) - (inner_radius_ * inner_radius_));
}

ognovenko::rectangle_t ognovenko::Rubber::getFrameRect() const
{
  constexpr double diameter_multiplier = 2.0;
  const double diameter = diameter_multiplier * outer_radius_;
  return {diameter, diameter, outer_pos_};
}

void ognovenko::Rubber::move(const ognovenko::point_t& pos)
{
  validateFinitePosition(pos);
  const double dx = pos.x - inner_pos_.x;
  const double dy = pos.y - inner_pos_.y;
  const ognovenko::point_t new_outer_pos = {outer_pos_.x + dx, outer_pos_.y + dy};
  validateFinitePosition(new_outer_pos);
  outer_pos_ = new_outer_pos;
  inner_pos_ = pos;
}

void ognovenko::Rubber::move(double dx, double dy)
{
  if (!std::isfinite(dx) || !std::isfinite(dy))
  {
    throw std::invalid_argument("Rubber displacement must be finite");
  }
  const ognovenko::point_t new_inner_pos = {inner_pos_.x + dx, inner_pos_.y + dy};
  const ognovenko::point_t new_outer_pos = {outer_pos_.x + dx, outer_pos_.y + dy};
  validateFinitePosition(new_inner_pos);
  validateFinitePosition(new_outer_pos);
  inner_pos_ = new_inner_pos;
  outer_pos_ = new_outer_pos;
}

void ognovenko::Rubber::scale(double factor)
{
  validatePositiveFinite(factor, "Scale factor must be positive and finite");
  const ognovenko::point_t new_outer_pos = {
    inner_pos_.x + ((outer_pos_.x - inner_pos_.x) * factor),
    inner_pos_.y + ((outer_pos_.y - inner_pos_.y) * factor)
  };
  const double new_outer_radius = outer_radius_ * factor;
  const double new_inner_radius = inner_radius_ * factor;
  validateFinitePosition(new_outer_pos);
  validatePositiveFinite(new_outer_radius, "Scaled Rubber outer radius is out of range");
  validatePositiveFinite(new_inner_radius, "Scaled Rubber inner radius is out of range");
  outer_pos_ = new_outer_pos;
  outer_radius_ = new_outer_radius;
  inner_radius_ = new_inner_radius;
}
