
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace manhica
{
  int contains(const char* str, char symbol)
  {
    for (int i = 0; str[i] != '\0'; ++i)
    {
      if (str[i] == symbol)
      {
        return 1;
      }
    }

    return 0;
  }

  int buildUncommon(const char* first, const char* second, char* result, int capacity)
  {
    int pos = 0;

    for (int i = 0; second[i] != '\0'; ++i)
    {
      if (contains(first, second[i]) == 0)
      {
        if (pos + 1 >= capacity)
        {
          return -1;
        }

        result[pos++] = second[i];
      }
    }

    for (int i = 0; first[i] != '\0'; ++i)
    {
      if (contains(second, first[i]) == 0)
      {
        if (pos + 1 >= capacity)
        {
          return -1;
        }

        result[pos++] = first[i];
      }
    }

    result[pos] = '\0';
    return pos;
  }

  int removeVowels(const char* source, char* result, int capacity)
  {
    int pos = 0;

    for (int i = 0; source[i] != '\0'; ++i)
    {
      const char symbol = static_cast< char >(std::tolower(static_cast< unsigned char >(source[i])));

      if (symbol != 'a' && symbol != 'e' && symbol != 'i' && symbol != 'o' && symbol != 'u')
      {
        if (pos + 1 >= capacity)
        {
          return -1;
        }

        result[pos++] = source[i];
      }
    }

    result[pos] = '\0';
    return pos;
  }

  char* readLine()
  {
    constexpr int initial_capacity = 16;
    int capacity = initial_capacity;
    int length = 0;

    char* buffer = static_cast< char* >(std::malloc(capacity));

    if (buffer == nullptr)
    {
      return nullptr;
    }

    int ch = 0;

    while ((ch = std::getchar()) != '\n' && ch != EOF)
    {
      if (length + 1 >= capacity)
      {
        if (capacity > INT_MAX / 2)
        {
          std::free(buffer);
          return nullptr;
        }

        capacity *= 2;

        char* const temp = static_cast< char* >(std::realloc(buffer, capacity));

        if (temp == nullptr)
        {
          std::free(buffer);
          return nullptr;
        }

        buffer = temp;
      }

      buffer[length++] = static_cast< char >(ch);
    }

    buffer[length] = '\0';
    return buffer;
  }
}

int main()
{
  const char* const second = "abc_ef";

  char* const input = manhica::readLine();

  if (input == nullptr)
  {
    std::fprintf(stderr, "Memory allocation error\n");
    return 1;
  }

  const int input_length = static_cast< int >(std::strlen(input));

  const int second_length = static_cast< int >(std::strlen(second));

  if (input_length > INT_MAX - second_length - 1)
  {
    std::fprintf(stderr, "String is too long\n");
    std::free(input);
    return 1;
  }

  const int capacity = input_length + second_length + 1;

  char* const uncommon = static_cast< char* >(std::malloc(capacity));

  char* const without_vowels = static_cast< char* >(std::malloc(input_length + 1));

  if (uncommon == nullptr || without_vowels == nullptr)
  {
    std::fprintf(stderr, "Memory allocation error\n");

    std::free(input);
    std::free(uncommon);
    std::free(without_vowels);

    return 1;
  }

  if (manhica::buildUncommon(input, second, uncommon, capacity) < 0
      || manhica::removeVowels(input, without_vowels, input_length + 1) < 0)
  {
    std::fprintf(stderr, "Transformation error\n");

    std::free(input);
    std::free(uncommon);
    std::free(without_vowels);

    return 1;
  }

  std::printf("%s\n", uncommon);
  std::printf("%s\n", without_vowels);

  std::free(input);
  std::free(uncommon);
  std::free(without_vowels);

  return 0;
}
