#include <iostream>
#include "rectangle.hpp"
#include "diamond.hpp"
#include "ring.hpp"

const double rect_width = 5.0;
const double rect_height = 3.0;
const point_t rect_center = {-3.0, 6.7};

const double diamond_d1 = 6.0;
const double diamond_d2 = 3.0;
const point_t diamond_center = {8.0, -9.0};

const double ring_r1 = 2.0;
const double ring_r2 = 4.0;
const point_t ring_center = {-5.0, -3.0};

const double two = 2.0;

rectangle_t getTotalFrame(Shape* shapes[], size_t size)
{
  const rectangle_t start_frame = shapes[0]->getFrameRect();
  double min_x = start_frame.pos.x - start_frame.width / two;
  double max_x = start_frame.pos.x + start_frame.width / two;
  double min_y = start_frame.pos.y - start_frame.height / two;
  double max_y = start_frame.pos.y + start_frame.height / two;

  for (size_t i = 0; i < size; ++i)
  {
    const rectangle_t current_frame = shapes[i]->getFrameRect();
    const double current_min_x = current_frame.pos.x - current_frame.width / two;
    const double current_max_x = current_frame.pos.x + current_frame.width / two;
    const double current_min_y = current_frame.pos.y - current_frame.height / two;
    const double current_max_y = current_frame.pos.y + current_frame.height / two;

    min_x = std::min(min_x, current_min_x);
    max_x = std::max(max_x, current_max_x);
    min_y = std::min(min_y, current_min_y);
    max_y = std::max(max_y, current_max_y);
  }

  const double total_width = max_x - min_x;
  const double total_height = max_y - min_y;
  const point_t frame_center = {min_x + total_width / two, min_y + total_height / two};
  return {total_width, total_height, frame_center};
}

void printInfo(Shape* shapes[], size_t size)
{
  double total_area = 0.0;
  for (size_t i = 0; i < size; ++i)
  {
    const double area = shapes[i]->getArea();
    total_area += area;
    const rectangle_t frame = shapes[i]->getFrameRect();

    std::cout << "Shape " << (i + 1) << ":\n";
    std::cout << "Area " << area << "\n";
    std::cout << "Frame: width = " << frame.width;
    std::cout << ", height = " << frame.height;
    std::cout << ", center = (" << frame.pos.x << ", " << frame.pos.y << ")\n";
  }

  std::cout << "Total area: " << total_area << "\n";
  const rectangle_t total_frame = getTotalFrame(shapes, size);

  std::cout << "Total frame: width = " << total_frame.width;
  std::cout << ", height = " << total_frame.height;
  std::cout << ", center = (" << total_frame.pos.x << ", " << total_frame.pos.y << ")\n";
}

void scaleShapes(Shape* shapes[], size_t size, const point_t& point, double ratio)
{
  for (size_t i = 0; i < size; ++i)
  {
    const point_t pos = shapes[i]->getFrameRect().pos;
    shapes[i]->scale(ratio);
    const point_t new_pos{point.x + (pos.x - point.x) * ratio, point.y + (pos.y - point.y) * ratio};
    shapes[i]->move(new_pos);
  }
}

void deleteShapes(Shape* shapes[], size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    delete shapes[i];
    shapes[i] = nullptr;
  }
}

int main()
{
  const size_t SIZE = 3;
  Shape* shapes[SIZE]{};
  try
  {
    shapes[0] = new Rectangle(rect_width, rect_height, rect_center);
    shapes[1] = new Diamond(diamond_d1, diamond_d2, diamond_center);
    shapes[2] = new Ring(ring_r1, ring_r2, ring_center);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    deleteShapes(shapes, SIZE);

    return 1;
  }

  std::cout << "Before scale:\n";
  printInfo(shapes, SIZE);

  std::cout << "Enter point coordinates and scale ratio: ";
  point_t point{};
  double ratio = 0.0;

  if (!(std::cin >> point.x >> point.y >> ratio))
  {
    std::cerr << "ERROR: invalid arguments\n";
    deleteShapes(shapes, SIZE);

    return 1;
  }

  try
  {
    scaleShapes(shapes, SIZE, point, ratio);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    deleteShapes(shapes, SIZE);

    return 1;
  }

  std::cout << "After scale:\n";
  printInfo(shapes, SIZE);

  deleteShapes(shapes, SIZE);

  return 0;
}
