#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

class Diamond: public Shape
{
public:
  Diamond(double d1, double d2, const point_t& center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& new_pos) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;

private:
  double d1_;
  double d2_;
  point_t center_;
};

#endif
