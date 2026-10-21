#include <cstddef>
#include <iostream>
#include <limits>

namespace ovsyannikov {
  const int invalid_input = 1;
  const int invalid_arguments = 2;
}

int main()
{
  const std::size_t max_size = std::numeric_limits< std::size_t >::max();
  std::size_t size = 0;
  int max = 0;
  std::size_t max_count = 0;
  int before_previous = 0;
  int previous = 0;
  std::size_t local_max_count = 0;

  int value = 0;
  while ((std::cin >> value) && (value != 0)) {
    if (size == max_size) {
      std::cerr << "sequence is too long\n";
      return ovsyannikov::invalid_arguments;
    }
    if ((size == 0) || (value > max)) {
      max = value;
      max_count = 0;
    }
    if (value == max) {
      ++max_count;
    }
    if ((size > 1) && (previous > before_previous) && (previous > value)) {
      ++local_max_count;
    }
    before_previous = previous;
    previous = value;
    ++size;
  }

  if (!std::cin) {
    std::cerr << "invalid input\n";
    return ovsyannikov::invalid_input;
  }
  if (size == 0) {
    std::cerr << "sequence is empty\n";
    return ovsyannikov::invalid_arguments;
  }
  std::cout << max_count << '\n' << local_max_count << '\n';
}
