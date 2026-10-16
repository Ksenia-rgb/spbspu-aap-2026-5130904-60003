#include <iostream>

int bigSmall(const int arr[], int n)
{
  int count = 0;
  for (int i = 0; i < (n - 2); i++)
  {
    if (arr[i] > arr[i + 1] && arr[i + 1] > arr[i + 2])
    {
      count++;
    }
  }
  return count;
}

int pifTr(const int arr[], int n)
{
  int count = 0;
  for (int i = 0; i < (n - 2); i++)
  {
    if (arr[i] * arr[i] + arr[i + 1] * arr[i + 1] == arr[i + 2] * arr[i + 2])
    {
      count++;
    }
    else if (arr[i] * arr[i] + arr[i + 2] * arr[i + 2] == arr[i + 1] * arr[i + 1])
    {
      count++;
    }
    else if (arr[i + 1] * arr[i + 1] + arr[i + 2] * arr[i + 2] == arr[i] * arr[i])
    {
      count++;
    }
  }
  return count;
}

int main()
{
  const int max_int = 1000;
  int big_small_count = 0;
  int pif_tr_count = 0;
  int x = 0;
  int c = 0;
  int arr[max_int]{};

  while (true)
  {
    std::cin >> x;
    if (std::cin.fail())
    {
      std::cerr << "ERROR: incorrect input data type" << "\n";
      return 1;
    }
    if (x == 0)
    {
      break;
    }
    if (c < max_int)
    {
      arr[c] = x;
      c++;
    }
  }

  if (c < 3)
  {
    std::cerr << "ERROR: incorrect sequence length" << "\n";
    return 2;
  }

  big_small_count = bigSmall(arr, c);
  pif_tr_count = pifTr(arr, c);

  std::cout << big_small_count << "\n";
  std::cout << pif_tr_count << "\n";
  return 0;
}
