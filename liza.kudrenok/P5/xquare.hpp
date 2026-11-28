#ifndef XQUARE_HPP
#define XQUARE_HPP
#include "shape.hpp"

namespace kudrenok
{
  class Xquare : public Shape
  {
  public:
    Xquare(double side, const point_t& pos);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    double side_;
    point_t pos_;
  };
}

#endif
