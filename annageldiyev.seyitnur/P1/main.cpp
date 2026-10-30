#include <iostream>

namespace annageldiyev {
  const int bad_sequence = 1;
}

int main()
{
  int num = 0;
  int past_num = 0;
  int past_past_num = 0;
  unsigned cnt_nums = 0;
  unsigned even_local = 0;
  unsigned max_even = 0;
  unsigned cnt = 0;

  while ((std::cin >> num) && (num != 0)) {
    if ((past_num < past_past_num) && (past_num > num) && (cnt >= 2)) {
      cnt_nums++;
    }
    if (num % 2 == 0) {
      even_local++;
      if (even_local > max_even) {
        max_even = even_local;
      }
    } else {
      even_local = 0;
    }
    past_past_num = past_num;
    past_num = num;
    cnt++;
  }

  if (std::cin.fail()) {
    std::cerr << "Bad sequence!";
    return annageldiyev::bad_sequence;
  }

  std::cout << max_even << "\n";
  std::cout << cnt_nums;
  return 0;
}
