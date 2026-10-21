#include <iostream>
#include <vector>

int countGrtLss(const std::vector<int>& a) {
    int count = 0;
    for (std::size_t i = 1; i + 1 < a.size(); ++i) {
        if (a[i] < a[i - 1] && a[i] > a[i + 1]) {
            ++count;
        }
    }
    return count;
}

int countEvnCnt(const std::vector<int>& a) {
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
    return 0;
}
