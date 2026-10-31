#include <cstddef>
#include <iostream>

namespace kovalenko {
  const int invalidInputCode = 1;
  const int calculationErrorCode = 2;
  const std::size_t secondMaxMinSize = 2;
  const std::size_t sumDupWindowSize = 2;
  const std::size_t sumDupMinSize = sumDupWindowSize + 1;

  static bool readSequence(std::size_t& size, int& second_max, std::size_t& sum_dup_count)
  {
    int max = 0;
    int previous = 0;
    int before_previous = 0;
    int current = 0;

    while (std::cin >> current) {
      if (current == 0) {
        return true;
      }
      const long long sum = static_cast< long long >(previous) + before_previous;
      if ((size >= sumDupWindowSize) && (current == sum)) {
        ++sum_dup_count;
      }
      if (size == 0) {
        max = current;
      } else if (current > max) {
        second_max = max;
        max = current;
      } else if ((size < secondMaxMinSize) || (current > second_max)) {
        second_max = current;
      }
      before_previous = previous;
      previous = current;
      ++size;
    }
    return false;
  }
}

int main()
{
  std::size_t size = 0;
  int second_max = 0;
  std::size_t sum_dup_count = 0;
  if (!kovalenko::readSequence(size, second_max, sum_dup_count)) {
    std::cerr << "Error: input is not a valid sequence of integers\n";
    return kovalenko::invalidInputCode;
  }

  int exit_code = 0;
  if (size >= kovalenko::sumDupMinSize) {
    std::cout << sum_dup_count << '\n';
  } else {
    std::cerr << "Error: cannot compute SUM-DUP, sequence is too short\n";
    exit_code = kovalenko::calculationErrorCode;
  }
  if (size >= kovalenko::secondMaxMinSize) {
    std::cout << second_max << '\n';
  } else {
    std::cerr << "Error: cannot compute SUB-MAX, sequence is too short\n";
    exit_code = kovalenko::calculationErrorCode;
  }
  return exit_code;
}
