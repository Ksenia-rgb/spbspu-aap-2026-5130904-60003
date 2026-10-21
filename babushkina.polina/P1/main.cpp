#include <iostream>

int main()
{
  int count = 0;
  int elem = 0;
  int max = 0;
  int sub_max = 0;
  bool sub_max_is_done = false;
  int prev = 0;
  int cur_len = 0;
  int mon_dec = 0;

  while (true)
  {
    if (!(std::cin >> elem))
    {
      std::cerr << "Error data format\n";
      return 1;
    }
    if (elem == 0)
    {
      break;
    }

    if (count == 0)
    {
      max = elem;
    }
    if (elem > max)
    {
      sub_max = max;
      sub_max_is_done = true;
      max = elem;
    }
    else if (elem < max && (elem > sub_max || !sub_max_is_done))
    {
      sub_max = elem;
      sub_max_is_done = true;
    }

    if (count == 0)
    {
      cur_len = 1;
    }
    else if (elem <= prev)
    {
      cur_len++;
    }
    else
    {
      cur_len = 1;
    }
    if (cur_len > mon_dec)
    {
      mon_dec = cur_len;
    }
    prev = elem;
    count++;
  }

  if (!(sub_max_is_done))
  {
    std::cerr << "ERROR: the sequence is too short\n";
    std::cout << mon_dec << "\n";
    return 2;
  }
  std::cout << sub_max << "\n";
  std::cout << mon_dec << "\n";
  return 0;
}
