#ifndef OGNOVENKO_XQUARE_HPP
#define OGNOVENKO_XQUARE_HPP

#include "shape.hpp"

namespace ognovenko
{
  class Xquare: public Shape
  {
  public:
    Xquare(const point_t& pos, double diagonal);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t pos_;
    double diagonal_;
  };
}

#endif
