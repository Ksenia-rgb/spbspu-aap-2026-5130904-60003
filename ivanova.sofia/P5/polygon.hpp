#include "shape.hpp"

class Polygon: public Shape
{
private:
  size_t count_;
  point_t* ptr_;

public:
  Polygon(const point_t* ptr, size_t count);
  ~Polygon() override;

  point_t getCentroid() const;

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& newPos) override;

  void move(const double delta_x, const double delta_y) override;

  void scale(double factor) override;

};
