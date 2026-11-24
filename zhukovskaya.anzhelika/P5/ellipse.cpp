#include "ellipse.hpp"
#include <iostream>

Ellipse::Ellipse(double rx, double ry, const point_t &cent)
    : rx_(rx), ry_(ry), centr_(cent) {
  if (rx <= 0 || ry <= 0)
  {
    throw std::invalid_argument("radiuses muse be >0");
  }
};

const double pi = 3.14159265;
double Ellipse::getArea() const { return pi * rx_ * ry_; }

rectangle_t Ellipse::getFrameRect() const { return {2 * rx_, 2 * ry_, centr_}; }

void Ellipse::move(double dx, double dy) {
  centr_.x += dx;
  centr_.y += dy;
}

void Ellipse::move(point_t &new_place) { centr_ = new_place; }

void Ellipse::scale(double ratio) {
  if (ratio <= 0)
  {
    throw std::invalid_argument("the ratio must be >0");
  }
  rx_ *= ratio;
  ry_ *= ratio;
}
