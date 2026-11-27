#include "rectangle.hpp"
#include <stdexcept>

namespace kudrenok
{
  Rectangle::Rectangle(double w, double h, const point_t& pos):
    box_{w, h, pos}
  {
    if (w <= 0.0 || h <= 0.0)
    {
      throw std::invalid_argument("Invalid rectangle size");
    }
  }

  double Rectangle::getArea() const
  {
    return box_.width * box_.height;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return box_;
  }

  void Rectangle::move(const point_t& pos)
  {
    box_.pos = pos;
  }

  void Rectangle::move(double dx, double dy)
  {
    box_.pos.x += dx;
    box_.pos.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid scale");
    }
    box_.width *= k;
    box_.height *= k;
  }
}
