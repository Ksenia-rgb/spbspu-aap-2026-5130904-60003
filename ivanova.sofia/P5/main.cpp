#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "base-types.hpp"
#include "ellipse.hpp"
#include "polygon.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

void scaleAroundPoint(Shape* shape, point_t center, double factor)
{
  if (shape == nullptr || factor <= 0.0)
  {
    throw std::invalid_argument("Invalid arguments for scaling");
  }

  point_t shapeCenter = shape->getFrameRect().pos_;
  const Polygon* poly = dynamic_cast<const Polygon*>(shape);
  if (poly != nullptr)
  {
    shapeCenter = poly->getCentroid();
  }

  double dx = (1.0 - factor) * (shapeCenter.x_ - center.x_);
  double dy = (1.0 - factor) * (shapeCenter.y_ - center.y_);

  shape->move(dx, dy);
  shape->scale(factor);
}

double getTotalArea(Shape** shapes, int count)
{
  double sum = 0.0;
  for (int i = 0; i < count; ++i)
  {
    sum += shapes[i]->getArea();
  }
  return sum;
}

rectangle_t getTotalFrameRect(Shape** shapes, int count)
{
  rectangle_t first = shapes[0]->getFrameRect();
  double minX = first.pos_.x_ - first.width_ / 2.0;
  double maxX = first.pos_.x_ + first.width_ / 2.0;
  double minY = first.pos_.y_ - first.height_ / 2.0;
  double maxY = first.pos_.y_ + first.height_ / 2.0;

  for (int i = 1; i < count; ++i)
  {
    rectangle_t r = shapes[i]->getFrameRect();
    double left = r.pos_.x_ - r.width_ / 2.0;
    double right = r.pos_.x_ + r.width_ / 2.0;
    double bottom = r.pos_.y_ - r.height_ / 2.0;
    double top = r.pos_.y_ + r.height_ / 2.0;

    minX = std::min(minX, left);
    maxX = std::max(maxX, right);
    minY = std::min(minY, bottom);
    maxY = std::max(maxY, top);
  }

  rectangle_t result;
  result.width_ = maxX - minX;
  result.height_ = maxY - minY;
  result.pos_.x_ = (minX + maxX) / 2.0;
  result.pos_.y_ = (minY + maxY) / 2.0;
  return result;
}

void printShapes(Shape** shapes, int count)
{
  for (int i = 0; i < count; ++i)
  {
    rectangle_t r = shapes[i]->getFrameRect();
    std::cout << "Figure " << (i + 1)
              << ": area = " << shapes[i]->getArea()
              << ", frame = (" << r.width_ << ", " << r.height_
              << ", pos = (" << r.pos_.x_ << ", " << r.pos_.y_ << "))\n";
  }

  rectangle_t totalR = getTotalFrameRect(shapes, count);
  std::cout << "Total area = " << getTotalArea(shapes, count) << '\n';
  std::cout << "Total frame = (" << totalR.width_ << ", " << totalR.height_
            << ", pos = (" << totalR.pos_.x_ << ", " << totalR.pos_.y_ << "))\n";
}

void freeShapes(Shape* shapes[], int count)
{
  for (int i = 0; i < count; ++i)
  {
    delete shapes[i];
  }
}

int main()
{
  const int count = 3;
  Shape* shapes[count] = {nullptr, nullptr, nullptr};

  point_t pts[3] = {{2.0, 2.0}, {6.0, 2.0}, {4.0, 6.0}};

  try
  {
    shapes[0] = new Rectangle(6.0, 4.0, {3.0, 2.0});
    shapes[1] = new Ellipse({0.0, 0.0}, 3.0, 2.0);
    shapes[2] = new Polygon(pts, 3);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    freeShapes(shapes, count);
    return 1;
  }

  std::cout << "Before scaling:\n";
  printShapes(shapes, count);

  double point_x = 0.0;
  double point_y = 0.0;
  double factor = 0.0;

  std::cout << "Enter center X and Y: ";
  if (!(std::cin >> point_x >> point_y)) {
    std::cerr << "Error: X and Y must be numbers\n";
    freeShapes(shapes, count);
    return 1;
  }

  if (factor <= 0.0) {
    std::cerr << "Error: factor must be over 0\n";
    freeShapes(shapes, count);
    return 1;
  }

  try {
    point_t center = {point_x, point_y};
    for (int i = 0; i < count; ++i) {
      scaleAroundPoint(shapes[i], center, factor);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    freeShapes(shapes, count);
    return 1;
  }

  std::cout << "\nAfter scaling:\n";
  printShapes(shapes, count);

  freeShapes(shapes, count);
  return 0;
}
