#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

namespace chacha {
class Diamond : public Shape {
 public:
  Diamond(double h_diag, double v_diag, const point_t& center);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double dx, double dy) override;
  void move(const point_t& newPos) override;

 private:
  double h_diag_;
  double v_diag_;
  point_t center_;
};
}  // namespace chacha

#endif
