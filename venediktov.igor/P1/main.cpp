#include <iostream>

int main()
{
  int min = 0;
  int count_min = 0;
  int count_div = 0;

  int prev = 0;
  bool first = true;

  int count_global = 0;
  int x = 0;

  while (std::cin >> x)
  {
    if (first)
    {
      if (x == 0)
      {
        std::cerr << "Error: enter a number, which is not a 0.\n";
        return 2;
      }

      first = false;
      prev = x;
      min = x;
      count_global += 1;
    }

    else if ((count_global > 0) && (!first))
    {
      if (x == 0)
      {
        if (count_global == 1)
        {
          std::cerr << "Error: not enough numbers.\n";
          return 2;
        }
        std::cout << count_min << "\n";
        std::cout << count_div << "\n";

        break;
      }

      if (x < min)
      {
        min = x;
        count_min = 1;
      }

      else if (x == min)
      {
        count_min += 1;
      }

      if (x % prev == 0)
      {
        count_div += 1;
      }

      prev = x;
      count_global += 1;
    }
  }

  if (std::cin.fail())
  {
    std::cerr << "Error: invalid input.\n";
    return 1;
  }

  return 0;
}
