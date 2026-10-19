#include <iostream>

int main()
{
  int current = 0;
  int prev = 0;
  int next = 0;

  bool has_prev = false;
  bool has_current = false;

  int task10_count = 0;

  int current_even_streak = 0;
  int max_even_streak = 0;

  while (std::cin >> next && next != 0)
  {
    if (has_current)
    {
      if (has_prev && prev > current && current < next)
      {
        task10_count++;
      }

      if (current % 2 == 0)
      {
        current_even_streak++;
        if (current_even_streak > max_even_streak)
        {
          max_even_streak = current_even_streak;
        }
      }
      else
      {
        current_even_streak = 0;
      }
    }

    prev = current;
    current = next;
    has_prev = has_current;
    has_current = true;
  }

  std::cout << task10_count << "\n";
  std::cout << max_even_streak << "\n";

  return 0;
}
