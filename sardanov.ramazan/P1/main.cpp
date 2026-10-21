#include <iostream>

int main()
{
  int sign_changes = 0;
  int triples = 0;
  int element_count = 0;

  int before_prev = 0;
  int prev = 0;
  int curr = 0;

  while (true)
  {
    if (!(std::cin >> curr))
    {
      std::cerr << "Error: input is not a sequence of integers\n";
      return 1;
    }
    if (curr == 0)
    {
      break;
    }

    if (element_count >= 1)
    {
      const bool neg_to_pos = (prev < 0) && (curr > 0);
      const bool pos_to_neg = (prev > 0) && (curr < 0);
      if (neg_to_pos || pos_to_neg)
      {
        ++sign_changes;
      }
    }

    if (element_count >= 2)
    {
      if ((before_prev > 0) && (prev > 0) && (curr > 0))
      {
        const long long a = before_prev;
        const long long b = prev;
        const long long c = curr;
        if ((a * a + b * b) == (c * c))
        {
          ++triples;
        }
      }
    }

    before_prev = prev;
    prev = curr;
    ++element_count;
  }

  std::cout << sign_changes << '\n';
  std::cout << triples << '\n';
  return 0;
}
