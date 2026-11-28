#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "rectangle.hpp"
#include "rubber.hpp"
#include "xquare.hpp"

namespace ognovenko
{
  static rectangle_t getOverallFrameRect(const std::unique_ptr<Shape> shapes[], int count);
  static void printFrameRect(const rectangle_t& frame);
  static void printFigures(const std::unique_ptr<Shape> shapes[], const char* names[], int count);
  static void scaleAllFigures(std::unique_ptr<Shape> shapes[], point_t centers[], int count,
      const point_t& pivot, double factor);
}

ognovenko::rectangle_t ognovenko::getOverallFrameRect(
    const std::unique_ptr<ognovenko::Shape> shapes[], int count)
{
  constexpr double half = 0.5;
  const ognovenko::rectangle_t first = shapes[0]->getFrameRect();
  double left = first.pos.x - (first.width * half);
  double right = first.pos.x + (first.width * half);
  double bottom = first.pos.y - (first.height * half);
  double top = first.pos.y + (first.height * half);

  for (int i = 0; i < count; ++i)
  {
    const ognovenko::rectangle_t frame = shapes[i]->getFrameRect();
    const double current_left = frame.pos.x - (frame.width * half);
    const double current_right = frame.pos.x + (frame.width * half);
    const double current_bottom = frame.pos.y - (frame.height * half);
    const double current_top = frame.pos.y + (frame.height * half);
    if (current_left < left)
    {
      left = current_left;
    }
    if (current_right > right)
    {
      right = current_right;
    }
    if (current_bottom < bottom)
    {
      bottom = current_bottom;
    }
    if (current_top > top)
    {
      top = current_top;
    }
  }

  const double width = right - left;
  const double height = top - bottom;
  const ognovenko::point_t pos = {(left + right) * half, (bottom + top) * half};
  return {width, height, pos};
}

void ognovenko::printFrameRect(const ognovenko::rectangle_t& frame)
{
  std::cout << "  Frame rectangle: width = " << frame.width
      << ", height = " << frame.height
      << ", center = (" << frame.pos.x << ", " << frame.pos.y << ")\n";
}

void ognovenko::printFigures(const std::unique_ptr<ognovenko::Shape> shapes[],
    const char* names[], int count)
{
  double total_area = 0.0;
  for (int i = 0; i < count; ++i)
  {
    const double area = shapes[i]->getArea();
    const ognovenko::rectangle_t frame = shapes[i]->getFrameRect();
    std::cout << names[i] << '\n';
    std::cout << "  Area: " << area << '\n';
    ognovenko::printFrameRect(frame);
    total_area += area;
  }

  std::cout << "Total area: " << total_area << '\n';
  std::cout << "Overall frame rectangle:\n";
  ognovenko::printFrameRect(ognovenko::getOverallFrameRect(shapes, count));
}

void ognovenko::scaleAllFigures(std::unique_ptr<ognovenko::Shape> shapes[],
    ognovenko::point_t centers[], int count,
    const ognovenko::point_t& pivot, double factor)
{
  for (int i = 0; i < count; ++i)
  {
    const ognovenko::point_t new_center = {
      pivot.x + ((centers[i].x - pivot.x) * factor),
      pivot.y + ((centers[i].y - pivot.y) * factor)
    };
    if (!std::isfinite(new_center.x) || !std::isfinite(new_center.y))
    {
      throw std::invalid_argument("Scaled figure position is out of range");
    }
    shapes[i]->move(new_center);
    shapes[i]->scale(factor);
    centers[i] = new_center;
  }
}

int main()
{
  constexpr int error_exit_code = 1;
  constexpr int decimal_places = 2;
  const ognovenko::point_t rectangle_center = {-2.0, -1.0};
  const double rectangle_width = 4.0;
  const double rectangle_height = 2.0;
  const ognovenko::point_t xquare_center = {4.0, 1.0};
  const double xquare_diagonal = 3.0;
  const ognovenko::point_t rubber_outer_center = {8.0, 1.0};
  const double rubber_outer_radius = 5.0;
  const ognovenko::point_t rubber_inner_center = {9.0, 2.0};
  const double rubber_inner_radius = 1.5;
  ognovenko::point_t pivot = {};
  double factor = 0.0;
  if (!(std::cin >> pivot.x >> pivot.y >> factor) ||
      !std::isfinite(pivot.x) || !std::isfinite(pivot.y) ||
      !std::isfinite(factor) || factor <= 0.0)
  {
    std::cerr << "Invalid input: expected a point and a positive scale factor\n";
    return error_exit_code;
  }

  try
  {
    std::unique_ptr<ognovenko::Shape> shapes[] = {
      std::unique_ptr<ognovenko::Shape>(
          new ognovenko::Rectangle(rectangle_center, rectangle_width, rectangle_height)),
      std::unique_ptr<ognovenko::Shape>(
          new ognovenko::Xquare(xquare_center, xquare_diagonal)),
      std::unique_ptr<ognovenko::Shape>(
          new ognovenko::Rubber(rubber_outer_center, rubber_outer_radius,
              rubber_inner_center, rubber_inner_radius))
    };
    const char* names[] = {"Rectangle", "Xquare", "Rubber"};
    ognovenko::point_t centers[] = {rectangle_center, xquare_center, rubber_inner_center};
    const int count = static_cast<int>(sizeof(shapes) / sizeof(shapes[0]));

    std::cout << std::fixed << std::setprecision(decimal_places);
    std::cout << "Before scaling:\n";
    ognovenko::printFigures(shapes, names, count);

    ognovenko::scaleAllFigures(shapes, centers, count, pivot, factor);

    std::cout << "After scaling:\n";
    ognovenko::printFigures(shapes, names, count);
  }
  catch (const std::exception& error)
  {
    std::cerr << "Error: " << error.what() << '\n';
    return error_exit_code;
  }

  return 0;
}
