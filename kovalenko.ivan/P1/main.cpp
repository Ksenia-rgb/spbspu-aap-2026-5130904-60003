#include <iostream>

namespace kovalenko {

  struct SequenceResult {
    int sumDupCount;
    int secondMax;
    int elementCount;
    bool sumDupPossible;
    bool subMaxPossible;
  };

  bool readSequence(SequenceResult &result)
  {
    result.sumDupCount = 0;
    result.secondMax = 0;
    result.elementCount = 0;
    result.sumDupPossible = false;
    result.subMaxPossible = false;

    long long prevPrev = 0;
    long long prev = 0;

    long long maxValue = 0;
    long long secondMaxValue = 0;
    bool hasMax = false;
    bool hasSecondMax = false;

    long long current = 0;

    while (std::cin >> current) {
      if (current == 0) {
        break;
      }

      if (result.elementCount >= 2) {
        if (current == prevPrev + prev) {
          ++result.sumDupCount;
        }
      }

      prevPrev = prev;
      prev = current;

      if (!hasMax) {
        maxValue = current;
        hasMax = true;
      } else if (current > maxValue) {
        secondMaxValue = maxValue;
        hasSecondMax = true;
        maxValue = current;
      } else if (current < maxValue) {
        if (!hasSecondMax || current > secondMaxValue) {
          secondMaxValue = current;
          hasSecondMax = true;
        }
      } else {
        if (!hasSecondMax || current > secondMaxValue) {
          secondMaxValue = current;
          hasSecondMax = true;
        }
      }

      ++result.elementCount;
    }

    if (!std::cin && !std::cin.eof()) {
      return false;
    }

    if (result.elementCount >= 2) {
      result.sumDupPossible = true;
    }

    if (hasSecondMax) {
      result.subMaxPossible = true;
      result.secondMax = static_cast<int>(secondMaxValue);
    }

    return true;
  }

}

int main()
{
  using namespace kovalenko;

  SequenceResult result;

  if (!readSequence(result)) {
    std::cerr << "Error: input is not a sequence of integers." << std::endl;
    return 1;
  }

  bool hasError = false;

  // Задача 15: SUM-DUP
  if (!result.sumDupPossible) {
    std::cerr << "Error: cannot compute SUM-DUP "
              << "(sequence is too short)." << std::endl;
    hasError = true;
  } else {
    std::cout << result.sumDupCount << std::endl;
  }

  // Задача 2: SUB-MAX
  if (!result.subMaxPossible) {
    std::cerr << "Error: cannot compute SUB-MAX "
              << "(sequence is too short)." << std::endl;
    hasError = true;
  } else {
    std::cout << result.secondMax << std::endl;
  }

  if (hasError) {
    return 2;
  }

  return 0;
}
