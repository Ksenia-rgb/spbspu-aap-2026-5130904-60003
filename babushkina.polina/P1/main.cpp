#include <iostream>
#include <limits>

int main() {
  int count = 0;
  int elem = 0;
  int max = std::numeric_limits<int>::min();
  int sub_max = std::numeric_limits<int>::min();
  bool sub_maxIsDone = false;
  int prev = 0;
  int cur_len = 0;
  int mon_dec = 0;

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
        sub_max = max;
        sub_maxIsDone = true;
      }
      max = elem;
    } else if (elem < max && elem > sub_max) {
      sub_max = elem;
      sub_maxIsDone = true;
    }

    if (count == 0) {
      cur_len = 1;
    } else if (elem <= prev) {
      cur_len++;
      std::cout << elem << " " << prev << '\n';
    } else {
      cur_len = 1;
    }
    if (cur_len > mon_dec) {
      mon_dec = cur_len;
    }
    prev = elem;
    count++;
  }

  if (!(sub_maxIsDone)) {
    std::cerr << "ERROR: the sequence is too short\n";
    std::cout << mon_dec << "\n";
    return 2;
  }
  std::cout << sub_max << "\n";
  std::cout << mon_dec << "\n";
  return 0;
}
