#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(double width, double height, const point_t& center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& new_pos) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;

private:
  rectangle_t rect_;
};

#endif
