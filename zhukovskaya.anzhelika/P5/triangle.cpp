#include "triangle.hpp"
#include <cmath>
#include <iostream>
const double half = 0.5;
const double two = 2.0;
const double three = 3.0;

Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c)
    : a_(a), b_(b), c_(c) {}

point_t Triangle::getCenter() const
{
  return {(a_.x + b_.x + c_.x) / three, (a_.y + b_.y + c_.y) / three};
}

double Triangle::getArea() const
{
  return half * std::abs(a_.x * (b_.y - c_.y)
                        + b_.x * (c_.y - a_.y)
                        + c_.x * (a_.y - b_.y));
}

rectangle_t Triangle::getFrameRect() const
{
  const double minx = std::min(a_.x, std::min(b_.x, c_.x));
  const double miny = std::min(a_.y, std::min(b_.y, c_.y));
  const double maxx = std::max(a_.x, std::max(b_.x, c_.x));
  const double maxy = std::max(a_.y, std::max(b_.y, c_.y));
  return {maxx - minx, maxy - miny, {(maxx + minx) / two, (maxy + miny) / two}};
}

void Triangle::move(double dx, double dy)
{
  a_.x += dx;
  b_.x += dx;
  c_.x += dx;
  a_.y += dy;
  b_.y += dy;
  c_.y += dy;
}

void Triangle::move(point_t &new_place)
{
  const point_t center = getCenter();
  move(new_place.x - center.x, new_place.y - center.y);
}

void Triangle::scale(double ratio)
{
  if (ratio <= 0)
  {
    throw std::invalid_argument("the ratio must be >0");
  }
  const point_t center = getCenter();
  a_.x = center.x + ((a_.x - center.x) * ratio);
  b_.x = center.x + ((b_.x - center.x) * ratio);
  c_.x = center.x + ((c_.x - center.x) * ratio);

  a_.y = center.y + ((a_.y - center.y) * ratio);
  b_.y = center.y + ((b_.y - center.y) * ratio);
  c_.y = center.y + ((c_.y - center.y) * ratio);
}
