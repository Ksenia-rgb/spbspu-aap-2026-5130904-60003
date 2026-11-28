#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Triangle: public Shape
{
public:
  Triangle(point_t a, point_t b, point_t c);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &) override;
  void move(double, double) override;
  void scale(double) override;

private:
  point_t a_;
  point_t b_;
  point_t c_;
  point_t center_;
};

#endif
