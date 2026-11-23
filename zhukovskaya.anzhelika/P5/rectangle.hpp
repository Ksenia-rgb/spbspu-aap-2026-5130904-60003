#pragma once
#include "shape.hpp"
class Rectangle : public Shape {
private:
  rectangle_t rect_;
public:
  Rectangle(double width, double height, const point_t &center);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(point_t &new_place) override;
  void scale(double ratio) override;
};