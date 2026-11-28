#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "rectangle.hpp"
#include "rubber.hpp"
#include "somov.hpp"
#include "triangle.hpp"

static const std::size_t shapeCount = 3;

void printShapesInfo(const Shape* const* shapes)
{
  double full_area = 0.0;
  for (std::size_t i = 0; i < shapeCount; ++i)
  {
    std::cout << "Shape " << (i + 1) << " area: " << shapes[i]->getArea() << "\n";
    std::cout << "Frame rectangle: ";
    somov::printRectangle(shapes[i]->getFrameRect());
    full_area += shapes[i]->getArea();
  }
  std::cout << "Full area: " << full_area << "\n";

  const rectangle_t bigFrame = somov::getBigFrameRect(shapes[0], shapes[1], shapes[2]);
  std::cout << "Big frame Rectangle: ";
  somov::printRectangle(bigFrame);
}

int main()
{
  point_t scale_dot{0.0, 0.0};
  double factor = 0.0;
  Shape* shapes[shapeCount] = {nullptr, nullptr, nullptr};

  const int width_r = 10.0;
  const int height_r = 20.0;
  const point_t center_r = {0.0, 0.0};

  const point_t a_t = {1.0, 0.0};
  const point_t b_t = {2.0, 0.0};
  const point_t c_t = {0.0, 4.0};

  const int r1 = 10.0;
  const int r2 = 5.0;
  const point_t center_rub = {3.0, 3.0};
  const int dx = 2.0;
  const int dy = 2.0;

  const Rectangle s1(width_r, height_r, center_r);
  const Triangle s2(a_t, b_t, c_t);
  const Rubber s3(r1, r2, center_rub, dx, dy);

  std::cin >> scale_dot.x >> scale_dot.y >> factor;
  if (!std::cin)
  {
    shapes[0] = new Rectangle(s1);
    shapes[1] = new Triangle(s2);
    shapes[2] = new Rubber(s3);

    printShapesInfo(shapes);
    std::cerr << "ERROR: Incorrect input!\n";
    for (std::size_t i = 0; i < shapeCount; i++)
    {
      delete shapes[i];
    }
    return somov::incorrectParam;
  }

  try
  {
    shapes[0] = new Rectangle(s1);
    shapes[1] = new Triangle(s2);
    shapes[2] = new Rubber(s3);

    printShapesInfo(shapes);
    for (std::size_t i = 0; i < shapeCount; ++i)
    {
      somov::scaleByDot(*shapes[i], scale_dot, factor);
    }
    std::cout << "\n";

    printShapesInfo(shapes);
    std::cout << "\n";

    for (std::size_t i = 0; i < shapeCount; i++)
    {
      delete shapes[i];
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    for (std::size_t i = 0; i < shapeCount; i++)
    {
      delete shapes[i];
    }
    return somov::incorrectParam;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: Bad alloc!";
    for (std::size_t i = 0; i < shapeCount; i++)
    {
      delete shapes[i];
    }
    return somov::internalError;
  }

  return somov::correctExit;
}
