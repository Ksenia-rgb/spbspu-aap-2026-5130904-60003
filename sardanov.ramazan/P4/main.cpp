#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace sardanov
{
  void shrSym(const char* str, char* abc);
  int seqSym(const char* str);
}

int main()
{
  int capacity = 10;
  int len = 0;

  char* str = nullptr;
  char ch = 0;

  try
  {
    str = new char[capacity];

    while (std::cin.get(ch) && ch != '\n')
    {
      if (len == capacity - 1)
      {
        capacity *= 2;

        char* const temp = new char[capacity];

        for (int i = 0; i < len; i++)
        {
          temp[i] = str[i];
        }

        delete[] str;
        str = temp;
      }

      str[len] = ch;
      len = len + 1;
    }
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: not enough memory\n";
    delete[] str;
    return 1;
  }

  str[len] = '\0';

  int code = 0;

  if (len == 0)
  {
    std::cerr << "Error: empty input\n";
    code = 1;
  }
  else
  {
    char abc[] = "abcdefghijklmnopqrstuvwxyz";
    sardanov::shrSym(str, abc);
    std::cout << abc << '\n';
    std::cout << sardanov::seqSym(str) << '\n';
  }

  delete[] str;

  return code;
}

void sardanov::shrSym(const char* str, char* abc)
{
  std::size_t len = 0;
  while (str[len] != '\0')
  {
    len++;
  }
  for (std::size_t i = 0; i < len; i++)
  {
    for (std::size_t j = 0; abc[j] != '\0'; j++)
    {
      if (std::tolower(static_cast< unsigned char >(str[i])) == static_cast< int >(abc[j]))
      {
        std::memmove(abc + j, abc + j + 1, std::strlen(abc + j));
        break;
      }
    }
  }
}

int sardanov::seqSym(const char* str)
{
  std::size_t len = 0;
  while (str[len] != '\0')
  {
    len++;
  }
  int count = 0;
  for (std::size_t i = 1; i < len; i++)
  {
    if ((str[i]) == (str[i - 1]))
    {
      count++;
    }
  }
  return count;
}
