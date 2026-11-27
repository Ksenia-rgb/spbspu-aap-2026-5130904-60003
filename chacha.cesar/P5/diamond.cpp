#include "diamond.hpp"
#include <stdexcept>

namespace chacha
{
const double half = 0.5;

Diamond::Diamond(double h_diag, double v_diag, const point_t& center) :
  h_diag_(h_diag),
  v_diag_(v_diag),
  center_(center)
{
  if (h_diag <= 0 || v_diag <= 0)
  {
    throw std::invalid_argument("Diagonals must be positive");
  }
}

double Diamond::getArea() const
{
  return (h_diag_ * v_diag_) * half;
}

rectangle_t Diamond::getFrameRect() const
{
  return {h_diag_, v_diag_, center_};
}

void Diamond::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Diamond::move(const point_t& new_pos)
{
  center_ = new_pos;
}
}
