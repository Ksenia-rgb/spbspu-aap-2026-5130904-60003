#ifndef BUBBLE_HPP
#define BUBBLE_HPP
#include "shape.hpp"

namespace kudrenok
{
  class Bubble : public Shape
  {
  public:
    Bubble(const point_t& cpos, double rad, const point_t& pos);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    point_t cpos_;
    double rad_;
    point_t pos_;
  };
}

#endif
