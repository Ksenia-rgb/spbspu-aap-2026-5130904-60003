#include <iostream>

int main()
{
  int min = 0;
  int countMin = 0;
  int countDiv = 0;

  int prev = 0;
  bool first = true;

  int countGlobal = 0;
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
      countGlobal += 1;
    }

    else if ((countGlobal > 0) && (!first))
    {
      if (x == 0)
      {
        if (countGlobal == 1)
        {
          std::cerr << "Error: not enough numbers.\n";
          return 2;
        }
        std::cout << countMin << "\n";
        std::cout << countDiv << "\n";

        break;
      }

      if (x < min)
      {
        min = x;
        countMin = 1;
      }

      else if (x == min)
      {
        countMin += 1;
      }

      if (x % prev == 0)
      {
        countDiv += 1;
      }

      prev = x;
      countGlobal += 1;
    }
  }

  if (std::cin.fail())
  {
    std::cerr << "Error: invalid input.\n";
    return 1;
  }

  return 0;
}
