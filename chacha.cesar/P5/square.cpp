#include "square.hpp"

#include <stdexcept>

namespace chacha {
Square::Square(double side, const point_t& bottom_left) : side_(side) {
  if (side <= 0) {
    throw std::invalid_argument("El lado debe ser mayor a 0");
  }
  center_.x = bottom_left.x + side_ / 2.0;
  center_.y = bottom_left.y + side_ / 2.0;
}

double Square::getArea() const {
  return side_ * side_;
}

rectangle_t Square::getFrameRect() const {
  return {side_, side_, center_};
}

void Square::move(double dx, double dy) {
  center_.x += dx;
  center_.y += dy;
}

void Square::move(const point_t& newPos) {
  center_ = newPos;
}
}
