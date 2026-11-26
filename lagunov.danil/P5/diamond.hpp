#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

class Diamond: public Shape
{
public:
  Diamond(double d1, double d2, const point_t& center);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(const point_t& new_pos);
  void move(double dx, double dy);
  void scale(double ratio);

private:
  double d1_;
  double d2_;
  point_t center_;
};

#endif
