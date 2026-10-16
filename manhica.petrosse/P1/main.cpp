#include <iostream>
#include <cstdlib> // for std::atoi

// Task 1) INC-SEQ
void task1()
{
  int x = 0;
  int previous = 0;
  int readCount = 0;
  int counter = 0;

  while (std::cin >> x && x != 0)
  {
    readCount++;
    if (readCount > 1 && x > previous)
    {
      counter++;
    }
    previous = x;
  }

  std::cout << counter << "\n";
}

// Task 13) PTH-TRP
void task13()
{
  long long x = 0;
  long long a = 0;
  long long b = 0;
  int readCount = 0;
  int counter = 0;

  while (std::cin >> x && x != 0)
  {
    readCount++;
    if (readCount >= 3 && a * a + b * b == x * x)
    {
      counter++;
    }
    a = b;
    b = x;
  }

  std::cout << counter << "\n";
}

int main(int argc, char * argv[])
{
  int task = 0;

  if (argc == 2)
  {
    task = std::atoi(argv[1]);
  }
  else
  {
    std::cerr << "Enter variant number (1 or 13): ";
    if (!(std::cin >> task))
    {
      std::cerr << "Invalid input\n";
      return 1;
    }
    std::cerr << "Enter the sequence, ending with 0: ";
  }

  if (task == 1)
  {
    task1();
  }
  else if (task == 13)
  {
    task13();
  }
  else
  {
    std::cerr << "Unknown variant number\n";
    return 1;
  }

  return 0;
}
