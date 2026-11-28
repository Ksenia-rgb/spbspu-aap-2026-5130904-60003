#ifndef OGNOVENKO_BASE_TYPES_HPP
#define OGNOVENKO_BASE_TYPES_HPP

namespace ognovenko
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}

#endif
