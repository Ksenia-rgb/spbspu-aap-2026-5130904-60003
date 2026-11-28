#ifndef OGNOVENKO_RUBBER_HPP
#define OGNOVENKO_RUBBER_HPP

#include "shape.hpp"

namespace ognovenko
{
  class Rubber: public Shape
  {
  public:
    Rubber(const point_t& outer_pos, double outer_radius,
        const point_t& inner_pos, double inner_radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t outer_pos_;
    double outer_radius_;
    point_t inner_pos_;
    double inner_radius_;
  };
}

#endif
