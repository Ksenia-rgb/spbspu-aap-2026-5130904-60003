#include <iostream>
#include <stdexcept>
#include "square.hpp"
#include "diamond.hpp"

int main()
{
  using namespace chacha;

  const double sq_side = 5.0;
  const point_t sq_pos = {0.0, 0.0};
  const double dm_h_diag = 4.0;
  const double dm_v_diag = 6.0;
  const point_t dm_pos = {1.0, 1.0};

  try
  {
    const Square sq(sq_side, sq_pos);
    const Diamond dm(dm_h_diag, dm_v_diag, dm_pos);

    double scale = 1.0;
    if (!(std::cin >> scale))
    {
      std::cout << "Square area: " << sq.getArea() << "\n";
      std::cout << "Diamond area: " << dm.getArea() << "\n";
      throw std::invalid_argument("Error: invalid input");
    }

    if (scale <= 0)
    {
      std::cout << "Square area: " << sq.getArea() << "\n";
      std::cout << "Diamond area: " << dm.getArea() << "\n";
      throw std::invalid_argument("Error: scale must be positive");
    }

    std::cout << "Square area: " << sq.getArea() << "\n";
    std::cout << "Diamond area: " << dm.getArea() << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
