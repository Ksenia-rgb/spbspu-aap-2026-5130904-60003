#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "xquare.hpp"
#include "bubble.hpp"

namespace kudrenok
{
  const int successCode = 0;
  const int errorCode = 1;

  void scaleShape(Shape* shape, const point_t& pos, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid scale");
    }

    rectangle_t r1 = shape->getFrameRect();
    shape->move(pos);
    rectangle_t r2 = shape->getFrameRect();

    double dx = (r1.pos.x - r2.pos.x) * k;
    double dy = (r1.pos.y - r2.pos.y) * k;

    shape->scale(k);
    shape->move(dx, dy);
  }

  rectangle_t getTotalFrame(const Shape* const* shapes, size_t n)
  {
    if (n == 0)
    {
      return {0.0, 0.0, {0.0, 0.0}};
    }

    rectangle_t first = shapes[0]->getFrameRect();
    double minX = first.pos.x - first.width / 2.0;
    double maxX = first.pos.x + first.width / 2.0;
    double minY = first.pos.y - first.height / 2.0;
    double maxY = first.pos.y + first.height / 2.0;

    for (size_t i = 1; i < n; ++i)
    {
      rectangle_t box = shapes[i]->getFrameRect();
      double left = box.pos.x - box.width / 2.0;
      double right = box.pos.x + box.width / 2.0;
      double bottom = box.pos.y - box.height / 2.0;
      double top = box.pos.y + box.height / 2.0;

      if (left < minX)
      {
        minX = left;
      }
      if (right > maxX)
      {
        maxX = right;
      }
      if (bottom < minY)
      {
        minY = bottom;
      }
      if (top > maxY)
      {
        maxY = top;
      }
    }

    double w = maxX - minX;
    double h = maxY - minY;
    return {w, h, {minX + w / 2.0, minY + h / 2.0}};
  }

  void printShapes(const Shape* const* shapes, size_t n)
  {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
      double area = shapes[i]->getArea();
      rectangle_t box = shapes[i]->getFrameRect();
      sum += area;

      std::cout << "Shape " << i + 1 << ": area = " << area
                << ", frame = [w: " << box.width << ", h: " << box.height
                << ", pos: (" << box.pos.x << ", " << box.pos.y << ")]\n";
    }

    rectangle_t res = getTotalFrame(shapes, n);
    std::cout << "Total area = " << sum << "\n";
    std::cout << "Total frame = [w: " << res.width << ", h: " << res.height
              << ", pos: (" << res.pos.x << ", " << res.pos.y << ")]\n";
  }

  void deleteShapes(Shape** shapes, size_t n)
  {
    for (size_t i = 0; i < n; ++i)
    {
      delete shapes[i];
    }
  }
}

int main()
{
  const size_t n = 3;
  kudrenok::Shape* shapes[n] = {nullptr, nullptr, nullptr};

  try
  {
    shapes[0] = new kudrenok::Rectangle(4.0, 2.0, {1.0, 1.0});
    shapes[1] = new kudrenok::Xquare(2.0, {-2.0, 3.0});
    shapes[2] = new kudrenok::Bubble({0.0, 0.0}, 5.0, {1.0, 2.0});

    kudrenok::printShapes(shapes, n);

    kudrenok::point_t pos{0.0, 0.0};
    double k = 1.0;
    if (!(std::cin >> pos.x >> pos.y >> k) || k <= 0.0)
    {
      std::cerr << "Error: invalid input\n";
      kudrenok::deleteShapes(shapes, n);
      return kudrenok::errorCode;
    }

    for (size_t i = 0; i < n; ++i)
    {
      kudrenok::scaleShape(shapes[i], pos, k);
    }

    kudrenok::printShapes(shapes, n);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    kudrenok::deleteShapes(shapes, n);
    return kudrenok::errorCode;
  }

  kudrenok::deleteShapes(shapes, n);
  return kudrenok::successCode;
}
