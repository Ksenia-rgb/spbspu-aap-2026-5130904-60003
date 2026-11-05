#include <iostream>

namespace binkovsky
{
  int run()
  {
    int value = 0;
    int maximum = 0;
    int max_count = 0;
    int current_length = 0;
    int max_length = 0;
    int previous = 0;
    bool has_value = false;
    bool has_previous = false;
    bool terminated = false;

    while (std::cin >> value)
    {
      if (value == 0)
      {
        terminated = true;
        break;
      }

      if (!has_value)
      {
        maximum = value;
        max_count = 1;
        current_length = 1;
        max_length = 1;
        has_value = true;
      }
      else
      {
        if (value > maximum)
        {
          maximum = value;
          max_count = 1;
        }
        else if (value == maximum)
        {
          ++max_count;
        }

        if (has_previous && value >= previous)
        {
          ++current_length;
        }
        else
        {
          current_length = 1;
        }

        if (current_length > max_length)
        {
          max_length = current_length;
        }
      }

      previous = value;
      has_previous = true;
    }

    if (!terminated)
    {
      std::cerr << "Error: invalid input\n";
      return 1;
    }

    if (!has_value)
    {
      std::cout << max_length << '\n';
      std::cerr << "Error: sequence is empty for CNT-MAX\n";
      return 2;
    }

    std::cout << max_count << '\n';
    std::cout << max_length << '\n';

    return 0;
  }
}

int main()
{
  return binkovsky::run();
}
