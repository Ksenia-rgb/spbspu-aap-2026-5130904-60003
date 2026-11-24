#include <iostream>
#include <stdexcept>
#include "ellipse.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double r_width = 6.0;
const double r_height = 10.0;
const point_t r_pos = {2.0, 2.0};

const double ell_rx = 4.0;
const double ell_ry = 2.0;
const point_t ell_pos = {0.0, 0.0};

const point_t triangle_a = {-10.0, -2.0};
const point_t triangle_b = {-5.0, -10.0};
const point_t triangle_c = {0.0, 1.0};

const double div_two = 2.0;

rectangle_t getTotalFrame(Shape* shapes[], size_t size) {
  rectangle_t start_pnt = shapes[0]->getFrameRect();
  double minx = start_pnt.pos.x - start_pnt.width / div_two;
  double maxx = start_pnt.pos.x + start_pnt.width / div_two;
  double miny = start_pnt.pos.y - start_pnt.height / div_two;
  double maxy = start_pnt.pos.y + start_pnt.height / div_two;

  for (size_t i = 1; i < size; ++i) {
    rectangle_t s_pnt = shapes[i]->getFrameRect();
    double s_minx = s_pnt.pos.x - s_pnt.width / div_two;
    double s_maxx = s_pnt.pos.x + s_pnt.width / div_two;
    double s_miny = s_pnt.pos.y - s_pnt.height / div_two;
    double s_maxy = s_pnt.pos.y + s_pnt.height / div_two;

    minx = std::min(minx, s_minx);
    maxx = std::max(maxx, s_maxx);
    miny = std::min(miny, s_miny);
    maxy = std::max(maxy, s_maxy);
  }

  double total_width = maxx - minx;
  double total_height = maxy - miny;
  point_t total_pos = {minx + (total_width / div_two), miny + (total_height / div_two)};
  return {total_width, total_height, total_pos};
}

void scaleShape(Shape* shape, point_t &start, double ratio) {
  point_t pos_start = shape->getFrameRect().pos;
  shape->move(start);
  point_t pos_finish = shape->getFrameRect().pos;
  shape->scale(ratio);

  double dx = (pos_start.x - pos_finish.x) * ratio;
  double dy = (pos_start.y - pos_finish.y) * ratio;
  shape->move(dx, dy);
}

void printInfo(Shape* shapes[], size_t size) {
  double total_area = 0.0;
  for (size_t i = 0; i < size; ++i) {
    double area = shapes[i]->getArea();
    total_area += area;
    rectangle_t rect_frame = shapes[i]->getFrameRect();

    std::cout << "Shape " << (i + 1) << ":\n"
    << "area = " << area << "\n"
    << "frame: width = " << rect_frame.width << ", height = "
    << rect_frame.height << "\n"
    << "center = (" << rect_frame.pos.x << ", " << rect_frame.pos.y << ")\n";
  }

  std::cout << "Total area: " << total_area << "\n";
  rectangle_t total_frame = getTotalFrame(shapes, size);

  std::cout << "total frame: width = " << total_frame.width
  << ", height = " << total_frame.height
  << ", center = (" << total_frame.pos.x << ", " << total_frame.pos.y << ")\n";
}

int main() {
  const size_t shape_cnt = 3;
  Shape* shapes[shape_cnt] = {nullptr, nullptr, nullptr};
  try {
    shapes[0] = new Rectangle(r_width, r_height, r_pos);
    shapes[1] = new Ellipse(ell_rx, ell_ry, ell_pos);
    shapes[2] = new Triangle(triangle_a, triangle_b, triangle_c);
  }
  catch (const std::exception &e) {
    std::cerr << "error of figure creating" << e.what() << "\n";
    for (size_t i = 0; i < shape_cnt; ++i) {
      delete[] shapes[i];
    }
    return 1;
  }


  std::cout << "before scale: \n";
  printInfo(shapes, shape_cnt);

  std::cout << "enter coordinates of center and scale ratio: \n";
  point_t pnt;
  double ratio;

  if (!(std::cin >> pnt.x >> pnt.y >> ratio)) {
    std::cerr << "error: invalid arguments\n";
    for (size_t i = 0; i < shape_cnt; ++i) {
      delete shapes[i];
    }
    return 1;
  }
  if (ratio <= 0.0) {
    std::cerr << "the ratio must be >0\n";
    for (size_t i = 0; i < shape_cnt; ++i) {
      delete shapes[i];
    }
    return 1;
  }
  for (size_t i = 0; i < shape_cnt; ++i) {
    scaleShape(shapes[i], pnt, ratio);
  }
  std::cout << "after scale:\n";
  printInfo(shapes, shape_cnt);

  for (size_t i = 0; i < shape_cnt; ++i) {
    delete shapes[i];
  }

  return 0;
}
