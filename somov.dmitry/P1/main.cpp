#include <iostream>

namespace somov {
  const int bad_sequence = 1;
}

int main()
{
  int num = 0;
  int past_num = 0;
  int past_past_num = 0;
  unsigned length_local = 1;
  unsigned max_length = 1;
  unsigned cnt = 0;
  unsigned cnt_nums = 0;

  while ((std::cin >> num) && (num != 0)) {
    if ((num < past_num) && (past_num < past_past_num) && (past_past_num != 0)) {
      cnt_nums++;
    }
    if ((num >= past_num) && (past_num != 0)) {
      length_local++;
    } else {
      length_local = 1;
    }
    if (length_local > max_length) {
      max_length = length_local;
    }
    past_past_num = past_num;
    past_num = num;
    cnt++;
  }

  if (std::cin.fail()) {
    std::cerr << "Bad sequence!";
    return somov::bad_sequence;
  }
  if (cnt == 0) {
    max_length = 0;
  }

  std::cout << max_length << "\n";
  std::cout << cnt_nums;
  return 0;
}
