#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

namespace chacha
{
  class Square: public Shape
  {
  public:
    Square(double side, const point_t& bottom_left);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t& new_pos) override;

  private:
    double side_;
    point_t center_;
  };
}

#endif
