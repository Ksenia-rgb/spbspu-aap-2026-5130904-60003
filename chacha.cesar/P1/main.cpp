#include <iostream>

namespace chacha {
  struct Result {
    bool has_sub_max = false;
    int sub_max = 0;
    int max_even_run = 0;
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
        r.has_sub_max = true;
        max1 = x;
      } else if (!r.has_sub_max || x > max2) {
        max2 = x;
        r.has_sub_max = true;
      }
      ++count;

      if (x % 2 == 0) {
        ++run;
        if (run > r.max_even_run) {
          r.max_even_run = run;
        }
      } else {
        run = 0;
      }
    }
    r.sub_max = max2;
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
  if (r.has_sub_max) {
    std::cout << r.sub_max << '\n';
  } else {
    std::cerr << "Error: sequence is too short for SUB-MAX\n";
    code = 2;
  }
  std::cout << r.max_even_run << '\n';
  return code;
}
