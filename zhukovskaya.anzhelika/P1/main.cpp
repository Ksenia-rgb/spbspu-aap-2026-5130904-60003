#include <iostream>
#include <limits>
#include <stdexcept>

const int n = 10;
const int div_2 = 2;
const int error_count_code = 2;
const int error_code = 1;

int divCount(const int arr[n])
{
  int cnt = 0;
  for (int i = 0; i < n - 1; ++i)
  {
    if (arr[i + 1] == 0)
    {
      if (i < 1)
      {
        std::cerr << "not enough numbers for operation\n";
        return error_count_code;
      }
      break;
    }
    if (arr[i + 1] % arr[i] == 0)
    {
      cnt++;
    }
  }
  return cnt;
}

int cntEvenNumb(const int arr[n])
{
  int max_cnt = 0;
  int cnt = 1;
  bool flag = false;
  for (int i = 0; i < n - 1; ++i)
  {
    if (arr[i + 1] == 0)
    {
      break;
    }
    if (arr[i] % div_2 == 0)
    {
      flag = true;
    }
    if (arr[i] % div_2 == 0 && arr[i + 1] % div_2 == 0)
    {
      cnt++;
      if (cnt > max_cnt)
      {
        max_cnt = cnt;
      }
    }
    else
    {
      cnt = 1;
    }
  }
  if (!flag)
  {
    return 0;
  }
  return max_cnt;
}

void numbering(int arr[n])
void numbering(int arr[n])
{
  long long save = 1;
  int c = 0;
  for (int i = 0; i < n; ++i)
  {
    std::cout << "enter number, for breaking input enter '0'\n";
    std::cin >> save;
    if (std::cin.fail())
    {
      throw std::invalid_argument("error, only integer\n");
    }
    else if (save > std::numeric_limits< int >::max())
    {
      throw std::overflow_error("this number is too much");
    }
    else if (save < std::numeric_limits< int >::min())
    {
      throw std::underflow_error("this number too little");
    }

    if (save == 0)
    {
      break;
    }
    arr[c] = save;
    c++;
  }
  std::cout << "The number of divisible: " << divCount(arr) << "\n";
  std::cout << "Consecutive even-numbers: " << cntEvenNumb(arr) << "\n";
}

int main()
{
  int arr[n]{};
  try
  {
    numbering(arr);
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return error_code;
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << e.what();
    return error_code;
  }
  catch (const std::underflow_error &e)
  {
    std::cerr << e.what();
    return error_code;
  }
  return 0;
}
