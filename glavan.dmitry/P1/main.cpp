#include <iostream>

namespace glavan {
  int processSequence(std::istream &in, std::ostream &out, std::ostream &err)
  {
    long long prev_1 = 0;
    long long prev_2 = 0;
    unsigned long long count = 0;
    unsigned long long div_rem = 0;
    unsigned long long sum_dup = 0;
    int value = 0;

    while (true) {
      if (!(in >> value)) {
        err << "Error: input is not a sequence of integers\n";
        return 1;
      }
      if (value == 0) {
        break;
      }
      if (count >= 1 && value % prev_1 == 0) {
        ++div_rem;
      }
      if (count >= 2 && value == prev_2 + prev_1) {
        ++sum_dup;
      }
      prev_2 = prev_1;
      prev_1 = value;
      ++count;
    }

    int result = 0;

    if (count >= 2) {
      out << div_rem << '\n';
    } else {
      err << "Error: DIV-REM needs at least 2 elements\n";
      result = 2;
    }

    if (count >= 3) {
      out << sum_dup << '\n';
    } else {
      err << "Error: SUM-DUP needs at least 3 elements\n";
      result = 2;
    }

    return result;
  }
} // namespace glavan

int main()
{
  return glavan::processSequence(std::cin, std::cout, std::cerr);
}
