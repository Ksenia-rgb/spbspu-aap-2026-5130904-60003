#include <iostream>

namespace ognovenko
{
  void updateEqlSeq(const int value, const int prev, const int seen, int &run_len, int &max_len)
  {
    if (seen == 0 || value != prev)
    {
      run_len = 1;
    }
    else
    {
      ++run_len;
    }

    if (run_len > max_len)
    {
      max_len = run_len;
    }
  }

  void updateLocMin(const int value, const int prev, const int before_prev, const int seen, int &min_count)
  {
    if (seen >= 2 && prev < before_prev && prev < value)
    {
      ++min_count;
    }
  }
}

int main()
{
  int prev = 0;
  int before_prev = 0;
  int value = 0;
  int seen = 0;
  int run_len = 0;
  int max_len = 0;
  int min_count = 0;
  bool terminated = false;

  while (std::cin >> value)
  {
    if (value == 0)
    {
      terminated = true;
      break;
    }

    ognovenko::updateEqlSeq(value, prev, seen, run_len, max_len);
    ognovenko::updateLocMin(value, prev, before_prev, seen, min_count);

    before_prev = prev;
    prev = value;
    ++seen;
  }

  if (!terminated)
  {
    std::cerr << "INPUT ERROR\n";
    return 1;
  }

  std::cout << max_len << '\n';

  if (seen == 0)
  {
    std::cerr << "ERROR: length can't be zero\n";
    return 2;
  }

  std::cout << min_count << '\n';
  return 0;
}
