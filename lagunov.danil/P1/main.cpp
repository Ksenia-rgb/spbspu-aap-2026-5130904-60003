#include <iostream>

namespace lagunov
{
  const int INVALID_INPUT = 1;
}

int main()
{
  int input = 0;
  unsigned int greater_then_prev = 0;
  unsigned int longest_decreasing_seq = 0;
  int prev = 0;
  unsigned int current_seq = 1;
  while (std::cin >> input && input != 0)
  {
    if (prev == 0 && input != 0)
    {
      prev = input;
      longest_decreasing_seq = current_seq;
      continue;
    }
    if (input <= prev && input != 0)
    {
      ++current_seq;
    }
    else if (input > prev && input != 0)
    {
      ++greater_then_prev;
      current_seq = 1;
    }
    if (current_seq > longest_decreasing_seq)
    {
      longest_decreasing_seq = current_seq;
    }
    prev = input;
  }
  
  if (std::cin.fail())
  {
    std::cerr << "INVALID INPUT\n";
    return lagunov::INVALID_INPUT;
  }
  
  std::cout << greater_then_prev << '\n' << longest_decreasing_seq << '\n';

  return 0;
}
