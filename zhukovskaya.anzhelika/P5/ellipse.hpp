#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include "shape.hpp"
class Ellipse : public Shape
{
private:
  double rx_;
  double ry_;
  point_t centr_;

public:
  Ellipse(double rx, double ry, const point_t &cent);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t &new_place) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;
};
#endif
