#include <cctype>
#include <cstddef>
#include <iostream>
#include <new>

int read_string(char **str_ptr, size_t *capacity_ptr)
{
  int ch;
  size_t length = 0;

  while ((ch = std::cin.get()) != '\n' && ch != EOF)
  {
    if (length + 2 > *capacity_ptr)
    {
      *capacity_ptr *= 2;
      char *temp = *str_ptr;
      *str_ptr = new (std::nothrow) char[*capacity_ptr];

      if (*str_ptr == nullptr)
      {
        std::cerr << "Memory reallocation failed\n";
        delete[] temp;
        return 1;
      }

      for (size_t i = 0; i < length; i++)
      {
        (*str_ptr)[i] = temp[i];
      }
      delete[] temp;
    }
    (*str_ptr)[length] = static_cast<char>(ch);
    length++;
  }

  (*str_ptr)[length] = '\0';
  return 0;
}

int append_digits(char *dest, const char *src)
{
  int dest_len = 0;
  while (dest[dest_len] != '\0')
  {
    dest_len++;
  }

  int i = 0;
  while (src[i] != '\0')
  {
    if (std::isdigit(static_cast<unsigned char>(src[i])))
    {
      dest[dest_len] = src[i];
      dest_len++;
    }
    i++;
  }

  dest[dest_len] = '\0';

  return 0;
}

int has_repeated_digits(const char *str)
{
  int counts[10];

  int i = 0;
  while (i < 10)
  {
    counts[i] = 0;
    i++;
  }

  i = 0;
  while (str[i] != '\0')
  {
    unsigned char ch = static_cast<unsigned char>(str[i]);
    if (std::isdigit(ch))
    {
      int digit_index = ch - '0';

      counts[digit_index]++;

      if (counts[digit_index] > 1)
      {
        return 1;
      }
    }
    i++;
  }

  return 0;
}

int main()
{
  size_t cap1 = 50;
  char *dest = new (std::nothrow) char[cap1];

  if (dest == nullptr)
  {
    std::cerr << "Memory allocation failed\n";
    return 1;
  }

  if (read_string(&dest, &cap1) != 0)
  {
    delete[] dest;
    return 1;
  }

  const char *src = "g1h2k";

  int res2 = has_repeated_digits(dest);
  append_digits(dest, src);

  std::cout << dest << "\n";
  std::cout << res2 << "\n";

  delete[] dest;
  return 0;
}