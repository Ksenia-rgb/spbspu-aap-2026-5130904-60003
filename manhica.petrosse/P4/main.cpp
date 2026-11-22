
#include <climits>
#include <iostream>
#include <new>

namespace manhica {
  int contains(const char *str, char symbol)
  {
    for (int i = 0; str[i] != '\0'; ++i) {
      if (str[i] == symbol) {
        return 1;
      }
    }

    return 0;
  }

  int buildUncommon(const char *first, const char *second, char *result, int capacity)
  {
    int pos = 0;

    for (int i = 0; second[i] != '\0'; ++i) {
      if (contains(first, second[i]) == 0) {
        if (pos + 1 >= capacity) {
          return -1;
        }

        result[pos++] = second[i];
      }
    }

    for (int i = 0; first[i] != '\0'; ++i) {
      if (contains(second, first[i]) == 0) {
        if (pos + 1 >= capacity) {
          return -1;
        }

        result[pos++] = first[i];
      }
    }

    result[pos] = '\0';
    return pos;
  }

  int removeVowels(const char *source, char *result, int capacity)
  {
    int pos = 0;

    for (int i = 0; source[i] != '\0'; ++i) {
      const char symbol = source[i];

      if (symbol != 'a' && symbol != 'e' && symbol != 'i' && symbol != 'o' && symbol != 'u' && symbol != 'A'
          && symbol != 'E' && symbol != 'I' && symbol != 'O' && symbol != 'U') {
        if (pos + 1 >= capacity) {
          return -1;
        }

        result[pos++] = source[i];
      }
    }

    result[pos] = '\0';
    return pos;
  }

  char *readLine()
  {
    constexpr int initial_capacity = 16;
    int capacity = initial_capacity;
    int length = 0;

    char *buffer = new (std::nothrow) char[capacity];

    if (buffer == nullptr) {
      return nullptr;
    }

    int ch = 0;

    while ((ch = std::cin.get()) != '\n' && ch != std::char_traits< char >::eof()) {
      if (length + 1 >= capacity) {
        if (capacity > INT_MAX / 2) {
          delete[] buffer;
          return nullptr;
        }

        capacity *= 2;

        char *temp = new (std::nothrow) char[capacity];

        if (temp == nullptr) {
          delete[] buffer;
          return nullptr;
        }

        for (int i = 0; i < length; ++i) {
          temp[i] = buffer[i];
        }

        delete[] buffer;
        buffer = temp;
      }

      buffer[length++] = static_cast< char >(ch);
    }

    if (ch == std::char_traits< char >::eof() && length == 0) {
      delete[] buffer;
      return nullptr;
    }

    buffer[length] = '\0';
    return buffer;
  }
}

int main()
{
  const char *const second = "abc_ef";

  char *const input = manhica::readLine();

  if (input == nullptr) {
    std::cerr << "Input or memory allocation error\n";
    return 1;
  }

  int input_length = 0;

  while (input[input_length] != '\0') {
    ++input_length;
  }

  int second_length = 0;

  while (second[second_length] != '\0') {
    ++second_length;
  }

  if (input_length > INT_MAX - second_length - 1) {
    std::cerr << "String is too long\n";
    delete[] input;
    return 1;
  }

  const int capacity = input_length + second_length + 1;

  char *const uncommon = new (std::nothrow) char[capacity];
  char *const without_vowels = new (std::nothrow) char[input_length + 1];

  if (uncommon == nullptr || without_vowels == nullptr) {
    std::cerr << "Memory allocation error\n";

    delete[] input;
    delete[] uncommon;
    delete[] without_vowels;

    return 1;
  }

  if (manhica::buildUncommon(input, second, uncommon, capacity) < 0
      || manhica::removeVowels(input, without_vowels, input_length + 1) < 0) {
    std::cerr << "Transformation error\n";

    delete[] input;
    delete[] uncommon;
    delete[] without_vowels;

    return 1;
  }

  std::cout << uncommon << '\n';
  std::cout << without_vowels << '\n';

  delete[] input;
  delete[] uncommon;
  delete[] without_vowels;

  return 0;
}
