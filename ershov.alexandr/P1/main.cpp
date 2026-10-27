#include <iostream>

int main()
{
  int big_small_count = 0;
  int pif_tr_count = 0;
  int c = 0;
  int prev2 = 0;
  int prev1 = 0;
  int curr = 0;

  while (true)
  {
    int x = 0;
    std::cin >> x;

    if (std::cin.fail())
    {
      std::cerr << "ERROR: incorrect input data type\n";
      return 1;
    }

    if (x == 0)
    {
      break;
    }

    c++;
    prev2 = prev1;
    prev1 = curr;
    curr = x;

    if (c >= 3)
    {
      if (prev2 > prev1 && prev1 > curr)
      {
        big_small_count++;
      }

      if (prev2 * prev2 + prev1 * prev1 == curr * curr)
      {
        pif_tr_count++;
      }

      else if (prev2 * prev2 + curr * curr == prev1 * prev1)
      {
        pif_tr_count++;
      }

      else if (prev1 * prev1 + curr * curr == prev2 * prev2)
      {
        pif_tr_count++;
      }
    }
  }

  if (c < 3)
  {
    std::cerr << "ERROR: incorrect sequence lenght\n";
    return 2;
  }

  std::cout << big_small_count << "\n";
  std::cout << pif_tr_count << "\n";

  return 0;
}
