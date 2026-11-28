#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(double width, double height, point_t pos);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &) override;
  void move(double, double) override;
  void scale(double) override;

private:
  double width_;
  double height_;
  point_t center_;
};

#endif
