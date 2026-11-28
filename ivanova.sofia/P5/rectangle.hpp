#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle: public Shape
{
private:
  double width_;
  double height_;
  point_t pos_;

public:
  Rectangle(double width, double height, const point_t& pos);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& newPos) override;

  void move(const double delta_x, const double delta_y) override;

  void scale(double factor) override;
};

#endif
