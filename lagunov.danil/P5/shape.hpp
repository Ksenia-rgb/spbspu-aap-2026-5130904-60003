#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t& new_pos) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double ratio) = 0;
  virtual ~Shape() = default;
};

#endif
