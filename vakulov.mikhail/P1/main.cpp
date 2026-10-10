#include <cstddef>
#include <iostream>

namespace vakulov {
  const int invalid_input = 1;
}

int main()
{
  const std::size_t initial_length = 1;

  int prev_num = 0;
  int cur_num = 0;
  std::size_t max_grow = 0;
  std::size_t count_grow = 0;
  std::size_t count_swaps = 0;

  while (true) {
    std::cin >> cur_num;
    if (std::cin.fail()) {
      std::cerr << "Invalid input\n";
      return vakulov::invalid_input;
    }
    if (cur_num == 0) {
      break;
    }

    if ((count_grow == 0) || (cur_num < prev_num)) {
      count_grow = initial_length;
    } else {
      ++count_grow;
    }
    if (count_grow > max_grow) {
      max_grow = count_grow;
    }

    if ((prev_num != 0) && ((prev_num < 0) != (cur_num < 0))) {
      ++count_swaps;
    }
    prev_num = cur_num;
  }

  std::cout << max_grow << '\n' << count_swaps << '\n';
  return 0;
}
