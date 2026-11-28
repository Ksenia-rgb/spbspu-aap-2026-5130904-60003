#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <cstddef>
#include "base-types.hpp"

class Shape
{
public:
  virtual double getArea() const = 0;

  virtual rectangle_t getFrameRect() const = 0;

  virtual void move(const point_t& newPos) = 0;

  virtual void move(const double delta_x, const double delta_y) = 0;

  virtual void scale(double factor) = 0;

  virtual ~Shape() = default;
};

#endif
