#include <cstddef>
#include <iostream>

namespace kovalenko {
  const int invalidInputCode = 1;
  const int calculationErrorCode = 2;
  const std::size_t secondMaxMinSize = 2;
  const std::size_t sumDupWindowSize = 2;
  const std::size_t sumDupMinSize = sumDupWindowSize + 1;

  static bool readSequence(std::size_t& size, int& secondMax, std::size_t& sumDupCount)
  {
    int max = 0;
    int previous = 0;
    int beforePrevious = 0;
    int current = 0;

    while (std::cin >> current) {
      if (current == 0) {
        return true;
      }
      const long long sum = static_cast< long long >(previous) + beforePrevious;
      if ((size >= sumDupWindowSize) && (current == sum)) {
        ++sumDupCount;
      }
      if (size == 0) {
        max = current;
      }
      else if (current > max) {
        secondMax = max;
        max = current;
      }
      else if ((size < secondMaxMinSize) || (current > secondMax)) {
        secondMax = current;
      }
      beforePrevious = previous;
      previous = current;
      ++size;
    }
    return false;
  }
}

int main()
{
  std::size_t size = 0;
  int secondMax = 0;
  std::size_t sumDupCount = 0;
  if (!kovalenko::readSequence(size, secondMax, sumDupCount)) {
    std::cerr << "Error: input is not a valid sequence of integers\n";
    return kovalenko::invalidInputCode;
  }

  int exitCode = 0;
  if (size >= kovalenko::sumDupMinSize) {
    std::cout << sumDupCount << '\n';
  }
  else {
    std::cerr << "Error: cannot compute SUM-DUP, sequence is too short\n";
    exitCode = kovalenko::calculationErrorCode;
  }
  if (size >= kovalenko::secondMaxMinSize) {
    std::cout << secondMax << '\n';
  }
  else {
    std::cerr << "Error: cannot compute SUB-MAX, sequence is too short\n";
    exitCode = kovalenko::calculationErrorCode;
  }
  return exitCode;
}
