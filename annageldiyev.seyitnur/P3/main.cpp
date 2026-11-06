#include <cstddef>
#include <iostream>
#include <new>

namespace annageldiyev
{
  int hasRepeatingDigits(const char *str) noexcept
  {
    int seen[10] = {};
    for (; *str != '\0'; ++str)
    {
      const char c = *str;
      if (c >= '0' && c <= '9')
      {
        const int digit = c - '0';
        if (seen[digit] != 0)
        {
          return 1;
        }
        seen[digit] = 1;
      }
    }
    return 0;
  }

  char *readLine()
  {
    constexpr std::size_t kInitialCapacity = 16;
    std::size_t capacity = kInitialCapacity;
    std::size_t size = 0;
    char *buffer = nullptr;
    try
    {
      buffer = new char[capacity];
    }
    catch (const std::bad_alloc &)
    {
      return nullptr;
    }

    char ch = '\0';
    while (std::cin.get(ch) && ch != '\n')
    {
      if (size + 1 >= capacity)
      {
        const std::size_t newCapacity = capacity * 2;
        char *bigger = nullptr;
        try
        {
          bigger = new char[newCapacity];
        }
        catch (const std::bad_alloc &)
        {
          delete[] buffer;
          return nullptr;
        }
        for (std::size_t i = 0; i < size; ++i)
        {
          bigger[i] = buffer[i];
        }
        delete[] buffer;
        buffer = bigger;
        capacity = newCapacity;
      }
      buffer[size++] = ch;
    }
    buffer[size] = '\0';
    return buffer;
  }
}

int main()
{
  char *line = annageldiyev::readLine();
  if (line == nullptr)
  {
    std::cerr << "Error: not enough memory to read the string\n";
    return 1;
  }

  std::cout << annageldiyev::hasRepeatingDigits(line) << "\n";
  delete[] line;
  return 0;
}
