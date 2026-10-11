#include <iostream>
#include <vector>

int main() {
  std::vector<int> a;
  int x;
  while (std::cin >> x && x != 0) {
    a.push_back(x);
  }

  int count = 0;
  for (std::size_t i = 1; i + 1 < a.size(); ++i) {
    if (a[i] < a[i - 1] && a[i] > a[i + 1]) {
      ++count;
    }
  }

  std::cout << count << std::endl;
  return 0;
}
