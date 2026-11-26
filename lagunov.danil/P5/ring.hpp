#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"

const double PI = 3.1415926535;

class Ring: public Shape
{
public:
  Ring(double r1, double r2, const point_t& center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& new_pos) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;

private:
  double r1_;
  double r2_;
  point_t center_;
};

#endif
