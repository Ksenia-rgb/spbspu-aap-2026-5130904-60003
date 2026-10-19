#include <iostream>
<<<<<<< HEAD
#include <vector>

int countGrtLss(const std::vector<int> &a) {
  int count = 0;
  for (std::size_t i = 1; i + 1 < a.size(); ++i) {
    if (a[i] < a[i - 1] && a[i] > a[i + 1]) {
      ++count;
    }
  }
  return count;
}

int countEvnCnt(const std::vector<int> &a) {
  int max_run = 0;
  int current_run = 0;
  for (int v : a) {
    if (v % 2 == 0) {
      ++current_run;
      if (current_run > max_run) {
        max_run = current_run;
      }
    } else {
      current_run = 0;
    }
  }
  return max_run;
}

int main() {
  std::vector<int> a;
  int x;
  while (std::cin >> x && x != 0) {
    a.push_back(x);
  }

  std::cout << "Greater-Less: " << countGrtLss(a) << "\n";
  std::cout << "Consecutive even-numbers: " << countEvnCnt(a) << "\n";
=======

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

>>>>>>> 5dbb528 (Implement P1)
  return 0;
}
