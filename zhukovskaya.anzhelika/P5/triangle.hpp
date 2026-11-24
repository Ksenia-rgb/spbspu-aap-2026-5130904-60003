#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

class Triangle : public Shape  {
private:
  point_t a_, b_, c_;
public:
  Triangle(const point_t &a, const point_t &b,const point_t &c);
  point_t getCenter() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(point_t &new_place) override;
  void scale(double ratio) override;
};
#endif
