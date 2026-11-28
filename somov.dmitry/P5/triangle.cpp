#include "triangle.hpp"

#include <cmath>
#include <stdexcept>

#include "somov.hpp"

double getDistance(const point_t& p1, const point_t& p2)
{
  const double dx = p1.x - p2.x;
  const double dy = p1.y - p2.y;
  return std::sqrt((dx * dx) + (dy * dy));
}

Triangle::Triangle(point_t a, point_t b, point_t c):
  a_(a),
  b_(b),
  c_(c)
{
  const double doubledArea = ((b_.x - a_.x) * (c_.y - a_.y)) - ((b_.y - a_.y) * (c_.x - a_.x));
  if (std::abs(doubledArea) <= 0)
  {
    throw std::invalid_argument("ERROR: Incorrect triangle!");
  }

  center_.x = (a_.x + b_.x + c_.x) / 3;
  center_.y = (a_.y + b_.y + c_.y) / 3;
}

double Triangle::getArea() const
{
  const double half = 0.5;
  const double sideAB = getDistance(a_, b_);
  const double sideAC = getDistance(a_, c_);
  const double sideBC = getDistance(b_, c_);

  const double p = (sideAB + sideAC + sideBC) * half;
  return std::sqrt(p * (p - sideAB) * (p - sideAC) * (p - sideBC));
}

rectangle_t Triangle::getFrameRect() const
{
  const double half = 0.5;
  const double minX = somov::findMin(a_.x, b_.x, c_.x);
  const double minY = somov::findMin(a_.y, b_.y, c_.y);
  const double maxX = somov::findMax(a_.x, b_.x, c_.x);
  const double maxY = somov::findMax(a_.y, b_.y, c_.y);

  const double frameWidth = maxX - minX;
  const double frameHeight = maxY - minY;
  const double posX = minX + (frameWidth * half);
  const double posY = minY + (frameHeight * half);
  return {frameWidth, frameHeight, {posX, posY}};
}

void Triangle::move(const point_t& new_pos)
{
  a_.x = new_pos.x;
  a_.y = new_pos.y;
  b_.x = new_pos.x;
  b_.y = new_pos.y;
  c_.x = new_pos.x;
  c_.y = new_pos.y;
}

void Triangle::move(double dx, double dy)
{
  a_.x += dx;
  a_.y += dy;

  b_.x += dx;
  b_.y += dy;

  c_.x += dx;
  c_.y += dy;
}

void Triangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("ERROR: Incorrect factor for Triangle!");
  }
  a_.x = center_.x + factor * (a_.x - center_.x);
  a_.y *= center_.y + factor * (a_.y - center_.y);
  b_.x *= center_.x + factor * (b_.x - center_.x);
  b_.y *= center_.y + factor * (b_.y - center_.y);
  c_.x *= center_.x + factor * (c_.x - center_.x);
  c_.y *= center_.y + factor * (c_.x - center_.y);
}
