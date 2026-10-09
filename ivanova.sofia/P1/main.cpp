#include <iostream>

int main()
{
  int triple_counter = 0;
  int min_elements_counter = 0;

  int x = 0;
  int y = 0;
  int z = 0;

  int min_num = 0;

  if (!(std::cin >> x)) {
    std::cerr << "ERROR: x must be a number" << "\n";
    return 1;
  }

  if (x != 0) {
    min_num = x;
    min_elements_counter = 1;

    if (!(std::cin >> y)) {
      std::cerr << "ERROR: y must be a number" << "\n";
      return 1;
    }

    if (y != 0) {
      if (y < min_num) {
        min_num = y;
        min_elements_counter = 1;
      } else if (y == min_num) {
        min_elements_counter++;
      }

      while (true) {
        if (!(std::cin >> z)) {
          std::cerr << "ERROR: z must be a number" << "\n";
          return 1;
        }
        if (z == 0) {
          break;
        }

        if (z < min_num) {
          min_num = z;
          min_elements_counter = 1;
        } else if (z == min_num) {
          min_elements_counter++;
        }

        if ((x * x + y * y == z * z) || (x * x + z * z == y * y) || (y * y + z * z == x * x)) {
            triple_counter++;
        }

        x = y;
        y = z;
      }
    }
  }
  std::cout << triple_counter << "\n";
  std::cout << min_elements_counter << "\n";

  return 0;
}
