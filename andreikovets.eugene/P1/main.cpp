#include <iostream>

int main()
{
    int cur = 0;
    int prev = 0;
    long long count_more_prev = 0;
    long long cur_len = 1;

    long long max_len = 0;
    while (std::cin >> cur && cur != 0)
    {
        if (prev)
        {
            if (cur > prev)
            {
                count_more_prev += 1;
            }
            if (cur == prev)
            {
                cur_len += 1;
            }
            else
            {
                if (max_len < cur_len)
                {
                    max_len = cur_len;
                }
                cur_len = 1;
            }
        }
        prev = cur;
    }
    if (max_len < cur_len)
    {
        max_len = cur_len;
    }

    if (!std::cin)
    {
        std::cerr << "Wrong input\n";
        return 1;
    }
    std::cout << count_more_prev << "\n";
    std::cout << max_len << "\n";
    return 0;
}
