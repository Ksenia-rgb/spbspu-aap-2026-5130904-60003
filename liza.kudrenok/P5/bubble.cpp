#include "bubble.hpp"
#include <stdexcept>
namespace kudrenok
{
  Bubble::Bubble(const point_t& cpos, double rad, const point_t& pos):
    cpos_(cpos),
    rad_(rad),
    pos_(pos)
  {
    if (rad <= 0.0)
    {
      throw std::invalid_argument("Invalid radius");
    }

    double dx = pos_.x - cpos_.x;
    double dy = pos_.y - cpos_.y;
    double dist2 = dx * dx + dy * dy;

    if (dist2 == 0.0 || dist2 >= rad_ * rad_)
    {
      throw std::invalid_argument("Invalid center");
    }
  }

  double Bubble::getArea() const
  {
    const double pi = 3.1415;
    return pi * rad_ * rad_;
  }

  rectangle_t Bubble::getFrameRect() const
  {
    return {2.0 * rad_, 2.0 * rad_, cpos_};
  }

  void Bubble::move(const point_t& pos)
  {
    move(pos.x - pos_.x, pos.y - pos_.y);
  }

  void Bubble::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
    cpos_.x += dx;
    cpos_.y += dy;
  }

  void Bubble::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid scale");
    }
    rad_ *= k;
    cpos_.x = pos_.x + (cpos_.x - pos_.x) * k;
    cpos_.y = pos_.y + (cpos_.y - pos_.y) * k;
  }
}
