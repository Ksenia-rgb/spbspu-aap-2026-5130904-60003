#include <iostream>

int main()
{
  using std::cin;
  using std::cout;

  const int success_code = 0;
  const int error_code = 2;
  const int terminator = 0;

  int count = 0;

  int max_run = 0;
  int current_run = 0;
  int previous_for_run = 0;

  int local_maxima = 0;
  int prev_prev = 0;
  int prev = 0;
  bool has_prev = false;
  bool has_prev_prev = false;

  int value = 0;
  while (cin >> value && value != terminator)
  {
    ++count;

    if (count == 1)
    {
      current_run = 1;
      max_run = 1;
    }
    else
    {
      if (value == previous_for_run)
      {
        ++current_run;
      }
      else
      {
        current_run = 1;
      }

      if (current_run > max_run)
      {
        max_run = current_run;
      }
    }
    previous_for_run = value;

    if (has_prev_prev)
    {
      if (prev > prev_prev && prev > value)
      {
        ++local_maxima;
      }
    }

    prev_prev = prev;
    prev = value;
    has_prev_prev = has_prev;
    has_prev = true;
  }

  cout << max_run << "\n";

  if (count == 0)
  {
    return error_code;
  }

  cout << local_maxima << "\n";

  return success_code;
}
