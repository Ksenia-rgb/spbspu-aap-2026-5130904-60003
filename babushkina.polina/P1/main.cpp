#include <iostream>
#include <limits>

int main() {
  int count = 0;
  int elem = 0;
  int max = std::numeric_limits<int>::min();
  int subMax = std::numeric_limits<int>::min();
  bool subMaxIsDone = false;
  int prev = 0;
  int curLen = 0;
  int monDec = 0;

  while (true) {
    if (!(std::cin >> elem)) {
      std::cerr << "Error data format\n";
      return 1;
    }
    if (elem == 0) {
      break;
    }

    if (elem > max) {
      if (max != std::numeric_limits<int>::min()) {
        subMax = max;
        subMaxIsDone = true;
      }
      max = elem;
    } else if (elem < max && elem > subMax) {
      subMax = elem;
      subMaxIsDone = true;
    }

    if (count == 0) {
      curLen = 1;
    } else if (elem <= prev) {
      curLen++;
      std::cout << elem << " " << prev << '\n';
    } else {
      curLen = 1;
    }
    if (curLen > monDec) {
      monDec = curLen;
    }
    prev = elem;
    count++;
  }

  if (!(subMaxIsDone)) {
    std::cerr << "ERROR: the sequence is too short\n";
    std::cout << monDec << "\n";
    return 2;
  }
  std::cout << subMax << "\n";
  std::cout << monDec << "\n";
  return 0;
}
