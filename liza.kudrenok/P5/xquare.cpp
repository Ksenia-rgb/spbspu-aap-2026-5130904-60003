#include "xquare.hpp"
#include <cmath>
#include <stdexcept>

namespace kudrenok
{
  Xquare::Xquare(double side, const point_t& pos):
    side_(side),
    pos_(pos)
  {
    if (side <= 0.0)
    {
      throw std::invalid_argument("Invalid side");
    }
  }

  double Xquare::getArea() const
  {
    return side_ * side_;
  }

  rectangle_t Xquare::getFrameRect() const
  {
    double diag = side_ * std::sqrt(2.0);
    return {diag, diag, pos_};
  }

  void Xquare::move(const point_t& pos)
  {
    pos_ = pos;
  }

  void Xquare::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Xquare::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid scale");
    }
    side_ *= k;
  }
}
