#include <iostream>

int main()
{
  using std::cin;
  using std::cout;

  const int successCode = 0;
  const int errorCode = 2;
  const int terminator = 0;

  int count = 0;

  int maxRun = 0;
  int currentRun = 0;
  int previousForRun = 0;

  int localMaxima = 0;
  int prevPrev = 0;
  int prev = 0;
  bool hasPrev = false;
  bool hasPrevPrev = false;

  int value = 0;
  while (cin >> value && value != terminator)
  {
    ++count;

    if (count == 1)
    {
      currentRun = 1;
      maxRun = 1;
    }
    else
    {
      if (value == previousForRun)
      {
        ++currentRun;
      }
      else
      {
        currentRun = 1;
      }

      if (currentRun > maxRun)
      {
        maxRun = currentRun;
      }
    }
    previousForRun = value;

    if (hasPrevPrev)
    {
      if (prev > prevPrev && prev > value)
      {
        ++localMaxima;
      }
    }

    prevPrev = prev;
    prev = value;
    hasPrevPrev = hasPrev;
    hasPrev = true;
  }

  cout << maxRun << "\n";

  if (count == 0)
  {
    return errorCode;
  }

  cout << localMaxima << "\n";

  return successCode;
}
