#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace chacha
{
  const int initial_capacity = 16;
  const int alphabet_size = 256;

  char *commonSymbols(char *dest, const char *first, const char *second)
  {
    std::size_t n = 0;
    for (const char *p = first; *p != '\0'; ++p)
    {
      if (std::strchr(second, *p) == nullptr)
      {
        continue;
      }
      dest[n] = '\0';
      if (std::strchr(dest, *p) == nullptr)
      {
        dest[n++] = *p;
      }
    }
    dest[n] = '\0';
    return dest;
  }

  char *frequentTop(char *dest, const char *src)
  {
    std::size_t counts[alphabet_size] = {};
    int chosen[alphabet_size] = {};

    for (const char *p = src; *p != '\0'; ++p)
    {
      const unsigned char c = static_cast< unsigned char >(*p);
      if (!std::isspace(c))
      {
        ++counts[c];
      }
    }

    for (int step = 0; step < 3; ++step)
    {
      std::size_t best = 0;
      std::size_t best_count = 0;
      for (std::size_t i = 0; i < alphabet_size; ++i)
      {
        if (counts[i] > best_count)
        {
          best_count = counts[i];
          best = i;
        }
      }
      if (best_count == 0)
      {
        break;
      }
      chosen[best] = 1;
      counts[best] = 0;
    }

    std::size_t n = 0;
    for (std::size_t i = 0; i < alphabet_size; ++i)
    {
      if (chosen[i])
      {
        dest[n++] = static_cast< char >(i);
      }
    }
    dest[n] = '\0';
    return dest;
  }

  char *readLine(std::istream &in)
  {
    std::size_t capacity = initial_capacity;
    std::size_t size = 0;
    char *buf = new (std::nothrow) char[capacity];
    if (buf == nullptr)
    {
      return nullptr;
    }
    char c = '\0';
    while (in.get(c) && c != '\n')
    {
      if (size + 1 >= capacity)
      {
        const std::size_t new_capacity = capacity * 2;
        char *const bigger = new (std::nothrow) char[new_capacity];
        if (bigger == nullptr)
        {
          delete[] buf;
          return nullptr;
        }
        std::memcpy(bigger, buf, size);
        delete[] buf;
        buf = bigger;
        capacity = new_capacity;
      }
      buf[size++] = c;
    }
    buf[size] = '\0';
    return buf;
  }
}

int main()
{
  char *const input = chacha::readLine(std::cin);

  if (input == nullptr)
  {
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  if (input[0] == '\0')
  {
    std::cerr << "Error: empty input\n";
    delete[] input;
    return 1;
  }

  const char *const second = "abc ef";

  char *const common = new (std::nothrow) char[std::strlen(input) + 1];
  char *const top = new (std::nothrow) char[4];

  if (common == nullptr || top == nullptr)
  {
    std::cerr << "Error: not enough memory to store the result\n";
    delete[] input;
    delete[] common;
    delete[] top;
    return 1;
  }

  std::cout << chacha::commonSymbols(common, input, second) << "\n";
  std::cout << chacha::frequentTop(top, input) << "\n";

  delete[] input;
  delete[] common;
  delete[] top;
  return 0;
}
