#include "polygon.hpp"
#include<stdexcept>

Polygon::Polygon(const point_t* ptr, size_t count)
{
  if (ptr == nullptr || count < 3)
  {
    throw std::invalid_argument("Invalid polygon");
  }

  count_ = count;
  ptr_ = nullptr;

  try
  {
    ptr_ = new point_t[count_]{};

    for (size_t i = 0; i < count; i++)
    {
      ptr_[i] = ptr[i];
    }
  }
  catch(std::bad_alloc& e)
  {
    delete[] ptr_;
    ptr_ = nullptr;
  }
}

point_t Polygon::getCentroid() const
{
  double signed_area = 0.0;
  double cx = 0.0;
  double cy = 0.0;

  for (size_t i = 0; i < count_; ++i)
  {
    const size_t next = (i + 1) % count_;
    const double cross = ptr_[i].x_ * ptr_[next].y_ - ptr_[next].x_ * ptr_[i].y_;
    signed_area += cross;
    cx += (ptr_[i].x_ + ptr_[next].x_) * cross;
    cy += (ptr_[i].y_ + ptr_[next].y_) * cross;
  }

  signed_area *= 0.5;
  if (std::abs(signed_area) == 0.0)
  {
    double sum_x = 0.0;
    double sum_y = 0.0;
    for (size_t i = 0; i < count_; ++i)
    {
      sum_x += ptr_[i].x_;
      sum_y += ptr_[i].y_;
    }
    return {sum_x / static_cast<double>(count_), sum_y / static_cast<double>(count_)};
  }

  const double factor = 1.0 / (6.0 * signed_area);
  return {cx * factor, cy * factor};
}

double Polygon::getArea() const
{
  double total = 0.0;
  for (size_t i = 0; i < count_; i++)
  const size_t next = (i + 1) % count_;
  {
    total += ptr_[i].x_ * ptr_[next].y_ - ptr_[next].x_ * ptr_[i].y_;
  }
  total *= 0.5;
  return total;
}

rectangle_t Polygon::getFrameRect() const
{
  double min_x = ptr_[0].x_;
  double max_x = ptr_[0].x_;
  double min_y = ptr_[0].y_;
  double max_y = ptr_[0].y_;

  for (size_t i = 1; i < count_; i++)
  {
    if (ptr_[i].x_ < min_x)
    {
      min_x = ptr_[i].x_;
    }

    if (ptr_[i].x_ > max_x)
    {
      max_x = ptr_[i].x_;
    }

    if (ptr_[i].y_ < min_y)
    {
      min_y = ptr_[i].y_;
    }

    if (ptr_[i].y_ > max_y)
    {
      max_y = ptr_[i].y_;
    }
  }

  return {max_x - min_x, max_y - min_y, {(max_x + min_x) / 2.0, (max_y +  min_y) / 2.0}};
}

void Polygon::move(const point_t& newPos)
{
  const point_t center = getCentroid();
  move(newPos.x_ - center.x_, newPos.y_ - center.y_);
}

void Polygon::move(const double delta_x, const double delta_y)
{
  for (size_t i = 0; i < count_; i++)
  {
    ptr_[i].x_ += delta_x;
    ptr_[i].y_ += delta_y;
  }
}

void Polygon::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }

  const point_t center = getCentroid();

  for (size_t i = 0; i < count_; i++)
  {
    ptr_[i].x_ = center.x_ + (ptr_[i].x_ - center.x_) * factor;
    ptr_[i].y_ = center.y_ + (ptr_[i].y_ - center.y_) * factor;
  }
}

Polygon::~Polygon()
{
  delete[] ptr_;
}
