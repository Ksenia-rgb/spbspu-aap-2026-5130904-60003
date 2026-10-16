#include <iostream>

int main()
{
  int const  max = 100;
  int arr[max];
  int x;

  int count = 0;
  while ((count < max) && (std::cin >> x))
  {
    if (x == 0) break;
    arr[count++] = x;
  }

  if (std::cin.fail())
  {
    std::cerr << "INVALID!\n";
    return 1;
  }

  if (count < 2)
  {
    std::cerr << "Too short\n";
    return 2;
  }

  int locMinCount = 0;
  int maxI = 0;
  for (int i = 0; i < count; i++)
  {
    if (i == 0)
    {
      if (arr[i] < arr[i + 1]) locMinCount += 1;
    }
    else if (i == (count - 1))
    {
      if (arr[i] < arr[i - 1]) locMinCount += 1;
    }
    else
    {
      if ((arr[i] < arr[i - 1]) && (arr[i] < arr[i + 1])) locMinCount += 1;
    }

    if (arr[i] > arr[maxI]) maxI = i;
  }

  std::cout << "LOC-MIN: " << locMinCount << "\n";
  std::cout << "AFT-MAX: " << count - maxI - 1 << "\n";
}
