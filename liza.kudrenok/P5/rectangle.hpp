#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace kudrenok
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double w, double h, const point_t& pos);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    rectangle_t box_;
  };
}

#endif
