#include <iostream>

namespace chacha {
  struct Result {
    bool hasSubMax = false;
    int subMax = 0;
    int maxEvenRun = 0;
  };
  bool process(std::istream &in, Result &r)
  {
    int x = 0;
    int count = 0;
    int max1 = 0;
    int max2 = 0;
    int run = 0;

    while (true) {
      if (!(in >> x)) {
        return false;
      }
      if (x == 0) {
        break;
      }

      if (count == 0) {
        max1 = x;
      } else if (x > max1) {
        max2 = max1;
        r.hasSubMax = true;
        max1 = x;
      } else if (!r.hasSubMax || x > max2) {
        max2 = x;
        r.hasSubMax = true;
      }
      ++count;

      if (x % 2 == 0) {
        ++run;
        if (run > r.maxEvenRun) {
          r.maxEvenRun = run;
        }
      } else {
        run = 0;
      }
    }
    r.subMax = max2;
    return true;
  }
}
int main()
{
  chacha::Result r;
  if (!chacha::process(std::cin, r)) {
    std::cerr << "Error: input is not a valid sequence\n";
    return 1;
  }

  int code = 0;
  if (r.hasSubMax) {
    std::cout << r.subMax << '\n';
  } else {
    std::cerr << "Error: sequence is too short for SUB-MAX\n";
    code = 2;
  }
  std::cout << r.maxEvenRun << '\n';
  return code;
}
