#include "ellipse.hpp"
#include<stdexcept>

Ellipse::Ellipse(const point_t& pos, double radius_x, double radius_y) {

  if (radius_x <= 0 || radius_y <= 0) {
    throw std::invalid_argument("Invalid ellipse");
  }

  pos_ = pos;
  rx_ = radius_x;
  ry_ = radius_y;
}

double Ellipse::getArea() const{
  const double pi = 3.14;
  return pi * rx_ * ry_;
}

rectangle_t Ellipse::getFrameRect() const {
  return {rx_ * 2.0, ry_ * 2.0, pos_};
}

void Ellipse::move(const point_t& newPos) {
  pos_ = newPos;
}

void Ellipse::move(const double delta_x, const double delta_y) {
  pos_.x_ += delta_x;
  pos_.y_ += delta_y;
}

void Ellipse::scale(double factor) {
  if (factor <= 0) {
    throw std::invalid_argument("Scale factor must be positive");
  }
  rx_ *= factor;
  ry_ *= factor;
}
