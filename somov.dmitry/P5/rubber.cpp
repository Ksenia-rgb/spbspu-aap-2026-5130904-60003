#include "rubber.hpp"
#include <stdexcept>

Rubber::Rubber(double r1, double r2, point_t center, double dx, double dy):
  min_r_((r1 > r2) ? r2 : r1),
  max_r_((r1 > r2) ? r1 : r2),
  center_(center),
  dx_(dx),
  dy_(dy)
{}

double Rubber::getArea() const
{
  const double pi = 3.1415;
  const double bigCircle = pi * max_r_ * max_r_;
  const double smallCircle = pi * min_r_ * min_r_;
  return bigCircle - smallCircle;
}

rectangle_t Rubber::getFrameRect() const
{
  const double diameterFactor = 2.0;
  const point_t frame_center = {center_.x + dx_, center_.y + dy_};
  return {diameterFactor * max_r_, diameterFactor * max_r_, frame_center};
}

void Rubber::move(const point_t& new_center)
{
  center_ = new_center;
}

void Rubber::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rubber::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("ERROR: Incorrect factor!");
  }
  min_r_ *= factor;
  max_r_ *= factor;
}
