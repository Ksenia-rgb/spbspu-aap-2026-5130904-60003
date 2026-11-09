#include <iostream>
#include <cctype>
#include <cstring>

namespace babushkina {
  void deleteDigits(const char *string, size_t size, char *result)
  {
    size_t j = 0;
    for (size_t i = 0; i < size; i++) {
      if (!(std::isdigit(static_cast< unsigned char >(string[i])))) {
        result[j++] = string[i];
      }
    }
    result[j] = '\0';
  }

  void upperToLower(const char *string, size_t size, char *result)
  {
    size_t j = 0;
    for (size_t i = 0; i < size; i++) {
      if (std::isupper(static_cast< unsigned char >(string[i]))) {
        result[j++] = static_cast< char >(tolower(static_cast< unsigned char >(string[i])));
      } else {
        result[j++] = string[i];
      }
    }
    result[j] = '\0';
  }
}

int main()
{
  char *input = nullptr;
  size_t str_len = 0;
  size_t buf_size = 10;

  try {
    input = new char[buf_size];
  } catch (const std::bad_alloc &) {
    std::cerr << "ERROR: memory allocation failed\n";
    return 1;
  }

  char ch = '\0';
  while (std::cin.get(ch) && ch != '\n') {
    if (str_len + 1 >= buf_size) {
      buf_size += 10;
      char *tmp_buf = nullptr;

      try {
        tmp_buf = new char[buf_size];
      } catch (const std::bad_alloc &) {
        std::cerr << "ERROR: memory allocation failed\n";
        delete[] input;
        return 1;
      }
      input[str_len] = '\0';
      std::strcpy(tmp_buf, input);
      delete[] input;
      input = tmp_buf;
    }
    input[str_len++] = ch;
  }

  if (std::cin.bad()) {
    std::cerr << "ERROR: input stream error\n";
    delete[] input;
    return 1;
  }
  if (str_len == 0) {
    std::cerr << "ERROR: no input\n";
    delete[] input;
    return 1;
  }
  input[str_len] = '\0';
  char *result1 = nullptr;
  char *result2 = nullptr;
  try {
    result1 = new char[str_len + 1]{};
    result2 = new char[str_len + 1]{};
  } catch (const std::bad_alloc &) {
    std::cerr << "ERROR: memory allocation failed\n";
    delete[] result1;
    delete[] result2;
    delete[] input;
    return 1;
  }

  babushkina::deleteDigits(input, str_len, result1);
  std::cout << result1 << "\n";
  babushkina::upperToLower(input, str_len, result2);
  std::cout << result2 << "\n";
  delete[] result1;
  delete[] result2;
  delete[] input;

  return 0;
}
