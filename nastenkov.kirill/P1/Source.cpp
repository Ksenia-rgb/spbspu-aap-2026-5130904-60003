#include <iostream>

int main() {
  long long max1 = 0, max2 = 0;
  long long prev = 0;
  long long count = 0;
  long long cur = 0, best = 0;
  bool terminated = false;

  long long x;
  while (std::cin >> x) {
    int next = std::cin.peek();
    if (next != EOF && next != ' ' && next != '\n' && next != '\t' &&
        next != '\r') {
      std::cerr << "Error: input is not a sequence of integers\n";
      return 1;
    }

    if (x == 0) {
      terminated = true;
      break;
    }
    if (count == 0) {
      max1 = x;
    } else if (count == 1) {
      if (x > max1) {
        max2 = max1;
        max1 = x;
      } else {
        max2 = x;
      }
    } else {
      if (x > max1) {
        max2 = max1;
        max1 = x;
      } else if (x > max2) {
        max2 = x;
      }
    }
    if (count > 0 && x >= prev)
      cur++;
    else
      cur = 1;
    if (cur > best)
      best = cur;

    prev = x;
    count++;
  }

  if (!terminated) {
    std::cerr << "Error: input is not a valid zero-terminated sequence\n";
    return 1;
  }

  int code = 0;

  if (count >= 2)
    std::cout << max2 << "\n";
  else {
    std::cerr << "Error: SUB-MAX cannot be calculated (sequence too short)\n";
    code = 2;
  }

  std::cout << best << "\n";

  return code;
}
