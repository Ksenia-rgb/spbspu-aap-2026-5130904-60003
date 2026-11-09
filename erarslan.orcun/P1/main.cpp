
#include <climits>
#include <cstddef>
#include <iostream>

namespace erarslan {
  int processSequence()
  {
    long long number = 0;
    long long maximum = 0;
    long long previous = 0;
    long long before_previous = 0;
    std::size_t length = 0;
    std::size_t maximum_count = 0;
    std::size_t sum_count = 0;
    bool terminated = false;

    while (std::cin >> number) {
      if (number == 0) {
        terminated = true;
        break;
      }

      if (length == 0 || number > maximum) {
        maximum = number;
        maximum_count = 1;
      } else if (number == maximum) {
        ++maximum_count;
      }

      if (length >= 2) {
        const bool overflow = (previous > 0 && before_previous > LLONG_MAX - previous)
            || (previous < 0 && before_previous < LLONG_MIN - previous);

        if (!overflow && before_previous + previous == number) {
          ++sum_count;
        }
      }

      before_previous = previous;
      previous = number;
      ++length;
    }

    if (!terminated) {
      std::cerr << "Invalid input sequence\n";
      return 1;
    }

    if (length == 0) {
      std::cerr << "Sequence is empty\n";
      return 2;
    }

    std::cout << maximum_count << '\n';

    if (length < 3) {
      std::cerr << "At least three elements are required for SUM-DUP\n";
      return 2;
    }

    std::cout << sum_count << '\n';
    return 0;
  }
}

int main()
{
  return erarslan::processSequence();
}
