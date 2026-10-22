#include <iostream>

int main()
{
  long long x = 0;
  long long previous = 0;
  long long before_previous = 0;

  int has_previous = 0;
  int has_two_previous = 0;

  int increasing_count = 0;
  int pythagorean_count = 0;

  while (std::cin >> x && x != 0) {
    if (has_previous && x > previous) {
      increasing_count++;
    }

    if (has_two_previous && before_previous * before_previous + previous * previous == x * x) {
      pythagorean_count++;
    }

    before_previous = previous;
    previous = x;

    has_two_previous = has_previous;
    has_previous = 1;
  }

  std::cout << increasing_count << "\n";
  std::cout << pythagorean_count << "\n";

  return 0;
}
