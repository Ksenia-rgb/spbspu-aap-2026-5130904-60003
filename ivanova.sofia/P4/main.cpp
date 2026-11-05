#include <cctype>
#include <cstring>
#include <iostream>
#include <new>

namespace ivanova {
int removeDigits(const char *source, char *destination, size_t size) {

  if (source == nullptr || destination == nullptr) {
    return 1;
  }

  if (size == 0) {
    return 2;
  }

  size_t j = 0;

  for (size_t i = 0; source[i] != '\0'; i++) {
    if (!std::isdigit(static_cast<unsigned char>(source[i]))) {
      if (j + 1 >= size) {
        return -1;
      }
      destination[j] = source[i];
      j++;
    }
  }

  destination[j] = '\0';
  return 0;
}

int convertToLower(const char *source, char *destination, size_t size) {

  if (source == nullptr || destination == nullptr) {
    return 1;
  }

  if (size == 0) {
    return 2;
  }

  size_t j = 0;

  for (size_t i = 0; source[i] != '\0'; i++) {

    if (j + 1 >= size) {
      return -1;
    }

    destination[j] = std::tolower(static_cast<unsigned char>(source[i]));
    j++;
  }
  destination[j] = '\0';
  return 0;
}

char *readStr() {

  size_t capacity = 8;
  size_t length = 0;

  char *str = new char[capacity]{};
  int ch = 0;

  while ((ch = std::cin.get()) != '\n' && ch != EOF) {

    if (length + 1 >= capacity) {
      size_t newCapacity = capacity * 2;
      try {
        char *newStr = new char[newCapacity]{};

        std::memcpy(newStr, str, length);

        delete[] str;
        str = newStr;
        capacity = newCapacity;
      } catch (...) {
        delete[] str;
        throw;
      }
    }

    str[length] = static_cast<char>(ch);
    length++;
  }

  str[length] = '\0';
  return str;
}
} // namespace ivanova

int main() {
  char *input = nullptr;
  char *result1 = nullptr;
  char *result2 = nullptr;

  try {
    input = ivanova::readStr();
    size_t length = std::strlen(input);

    result1 = new char[length + 1]{};
    result2 = new char[length + 1]{};

    if (ivanova::removeDigits(input, result1, length + 1) != 0) {
      delete[] input;
      delete[] result1;
      delete[] result2;
      std::cerr << "String conversion error\n";
      return 1;
    }
    std::cout << result1 << "\n";

    if (ivanova::convertToLower(input, result2, length + 1) != 0) {
      delete[] input;
      delete[] result1;
      delete[] result2;
      std::cerr << "String conversion error\n";
      return 1;
    }
    std::cout << result2 << "\n";

    delete[] input;
    delete[] result1;
    delete[] result2;
  } catch (const std::bad_alloc &) {
    delete[] input;
    delete[] result1;
    delete[] result2;
    std::cerr << "Memory allocation error\n";
    return 1;
  }
  return 0;
}
