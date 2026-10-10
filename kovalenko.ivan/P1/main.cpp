#include <iostream>
 
namespace kovalenko {
  static const int invalidInputCode = 1;
  static const int calculationErrorCode = 2;
  static const int secondMaxMinSize = 2;
  static const int sumDupMinSize = 3;
 
  static bool readSequence(int &size, int &secondMax, int &sumDupCount)
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
      if ((size >= (sumDupMinSize - 1)) && (current == sum)) {
        ++sumDupCount;
      }
 
      if (size == 0) {
        max = current;
      } else if (current > max) {
        secondMax = max;
        max = current;
      } else if ((size == 1) || (current > secondMax)) {
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
  int size = 0;
  int secondMax = 0;
  int sumDupCount = 0;
 
  if (!kovalenko::readSequence(size, secondMax, sumDupCount)) {
    std::cerr << "Error: input is not a valid sequence of integers\n";
    return kovalenko::invalidInputCode;
  }
 
  int exitCode = 0;
 
  if (size >= kovalenko::sumDupMinSize) {
    std::cout << sumDupCount << '\n';
  } else {
    std::cerr << "Error: cannot compute SUM-DUP, sequence is too short\n";
    exitCode = kovalenko::calculationErrorCode;
  }
 
  if (size >= kovalenko::secondMaxMinSize) {
    std::cout << secondMax << '\n';
  } else {
    std::cerr << "Error: cannot compute SUB-MAX, sequence is too short\n";
    exitCode = kovalenko::calculationErrorCode;
  }
 
  return exitCode;
}
