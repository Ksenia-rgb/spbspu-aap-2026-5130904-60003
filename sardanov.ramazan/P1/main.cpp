#include <iostream>

int main()
{
  const int invalid_input_code = 1;

  long long sign_changes = 0;
  long long triples = 0;
  long long element_count = 0;

  int before_previous = 0;
  int previous = 0;
  int current = 0;

  while (true)
  {
    if (!(std::cin >> current))
    {
      std::cerr << "Error: input is not a sequence of integers\n";
      return invalid_input_code;
    }
    if (current == 0)
    {
      break;
    }

    if (element_count >= 1)
    {
      const bool negative_to_positive = (previous < 0) && (current > 0);
      const bool positive_to_negative = (previous > 0) && (current < 0);
      if (negative_to_positive || positive_to_negative)
      {
        ++sign_changes;
      }
    }

    if (element_count >= 2)
    {
      if ((before_previous > 0) && (previous > 0) && (current > 0))
      {
        const long long a = before_previous;
        const long long b = previous;
        const long long c = current;
        if ((a * a + b * b) == (c * c))
        {
          ++triples;
        }
      }
    }

    before_previous = previous;
    previous = current;
    ++element_count;
  }

  std::cout << sign_changes << '\n';
  std::cout << triples << '\n';
  return 0;
}
