#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "shape.hpp"

class Ellipse: public Shape {
private:
  point_t pos_;
  double rx_;
  double ry_;

public:
  Ellipse(const point_t& pos, double radius_x, double radius_y);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& newPos) override;

  void move(const double delta_x, const double delta_y) override;

  void scale(double factor) override;
};

#endif
