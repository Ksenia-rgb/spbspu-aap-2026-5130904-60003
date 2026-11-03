#include <iostream>

int main()
{
  int pre_previous = 0, previous = 0, current = 0;
  int local_min = 0, max = 0, max_position = 0;
  int count = 0;

  while (std::cin >> current)
  {
    if (current != 0)
    {
      count++;
    }

    if (current > max)
    {
      max = current;
      max_position = count;
    }

    if (previous)
    {
      if (pre_previous)
      {
        if ((previous < pre_previous) && (previous < current))
        {
          local_min++;
        }

        if ((current == 0) && (previous < pre_previous))
        {
          local_min++;
        }
      }
      else if (previous < current)
      {
        local_min++;
      }

      pre_previous = previous;
    }

    if (current == 0)
    {
      break;
    }

    previous = current;
  }

  if (std::cin.fail())
  {
    std::cerr << "INVALID!\n";
    return 1;
  }

  if (count < 2)
  {
    std::cerr << "Too short\n";
    return 2;
  }

  std::cout << "LOC-MIN: " << local_min << "\n";
  std::cout << "AFT-MAX: " << count - max_position << "\n";
}
