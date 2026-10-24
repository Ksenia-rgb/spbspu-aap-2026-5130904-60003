#include <iostream>

namespace glavan {
  int processSequence()
  {
    int prev_1 = 0;
    int prev_2 = 0;
    int value = 0;
    int count = 0;
    int div_rem = 0;
    int sum_dup = 0;

    while (true) {
      if (!(std::cin >> value)) {
        std::cerr << "Error: input is not a sequence of integers\n";
        return 1;
      }
      if (value == 0) {
        break;
      }
      if (count >= 1 && value % prev_1 == 0) {
        ++div_rem;
      }
      if (count >= 2 && prev_2 + prev_1 == value) {
        ++sum_dup;
      }
      ++count;

      if (!(std::cin >> prev_2)) {
        std::cerr << "Error: input is not a sequence of integers\n";
        return 1;
      }
      if (prev_2 == 0) {
        break;
      }
      if (prev_2 % value == 0) {
        ++div_rem;
      }
      if (count >= 2 && prev_1 + value == prev_2) {
        ++sum_dup;
      }
      ++count;

      if (!(std::cin >> prev_1)) {
        std::cerr << "Error: input is not a sequence of integers\n";
        return 1;
      }
      if (prev_1 == 0) {
        break;
      }
      if (prev_1 % prev_2 == 0) {
        ++div_rem;
      }
      if (value + prev_2 == prev_1) {
        ++sum_dup;
      }
      ++count;
    }

    int result = 0;
    if (count >= 2) {
      std::cout << div_rem << '\n';
    } else {
      std::cerr << "Error: DIV-REM needs at least 2 elements\n";
      result = 2;
    }
    if (count >= 3) {
      std::cout << sum_dup << '\n';
    } else {
      std::cerr << "Error: SUM-DUP needs at least 3 elements\n";
      result = 2;
    }
    return result;
  }
}

int main()
{
  return glavan::processSequence();
}

