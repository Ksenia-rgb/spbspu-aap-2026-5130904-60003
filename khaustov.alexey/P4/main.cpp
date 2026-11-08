
#include <iostream>
#include <cstring>
#include <cctype>
#include <new>
#include <limits>

namespace khaustov
{
  void uppToLow(const char* input, char* result, size_t length)
  {
    for (int i = 0; i < length; i++) {
      result[i] = tolower(input[i]);
    }
    result[length] = '\0';
  }

  void uniteStrings(const char* input, size_t length_input, const char* second, size_t length_second, char* result)
  {
    size_t min_length;
    if (length_input < length_second) {
      min_length = length_input;
    } else {
      min_length = length_second;
    }
    for (int i = 0; i < min_length; i++) {
      result[i * 2] = input[i];
      result[i * 2 + 1] = second[i];
    }

    if (min_length == length_second) {
      for (int i = min_length; i < length_input; i++) {
        result[min_length + i] = input[i];
      }
    } else {
      for (int i = min_length; i < length_second; i++) {
        result[min_length + i] = second[i];
      }
    }
    result[length_input + length_second] = '\0';
  }
}

int main()
{
  char* input_string = nullptr;
  char* result11 = nullptr;
  char* result12 = nullptr;

  try
  {
    size_t current_max_size = 16;
    size_t length = 0;

    input_string = new char[current_max_size];

    char symbol;

    while (std::cin.get(symbol) && symbol != '\n')
    {
      if (length + 1 >= current_max_size)
      {
        if (current_max_size > std::numeric_limits<size_t>::max() / 2)
        {
          std::cerr << "Too long string\n";
          delete[] input_string;
          return 1;
        }

        size_t new_max_size = current_max_size * 2;
        char* new_string = new char[new_max_size];

        for (int i = 0; i < length; i++) {
          new_string[i] = input_string[i];
        }

        delete[] input_string;
        input_string = new_string;
        current_max_size = new_max_size;
      }
      input_string[length++] = symbol;
    }
    input_string[length] = '\0';

    result11 = new char[length + 1];
    khaustov::uppToLow(input_string, result11, length);
    std::cout << result11 << '\n';

    const char second[] = "def_";
    size_t resultSize = length + strlen(second) + 1;
    result12 = new char[resultSize];

    khaustov::uniteStrings(input_string, length, second, strlen(second), result12);
    std::cout << result12 << '\n';
  } catch (const std::bad_alloc&)
  {
    std::cerr << "Memory error\n";

    delete[] input_string;
    delete[] result11;
    delete[] result12;

    input_string = nullptr;
    result11 = nullptr;
    result12 = nullptr;

    return 1;
  }

  delete[] input_string;
  delete[] result11;
  delete[] result12;

  input_string = nullptr;
  result11 = nullptr;
  result12 = nullptr;

  return 0;
}
