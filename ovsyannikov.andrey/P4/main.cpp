#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace ovsyannikov {
  const int no_memory = 1;
  const int empty_input = 2;
  const std::size_t start_capacity = 16;
  const std::size_t resize_multi = 2;

  char * readLine(std::istream & in);
  int hasRepeats(const char * str);
  char * excludeSymbols(const char * str, const char * excluded, char * result);
}

char * ovsyannikov::readLine(std::istream & in)
{
  std::size_t capacity = start_capacity;
  char * str = new char[capacity];

  std::size_t size = 0;
  char symbol = '\0';
  while (in.get(symbol) && (symbol != '\n')) {
    if (size + 1 == capacity) {
      capacity *= resize_multi;
      char * bigger = nullptr;
      try {
        bigger = new char[capacity];
      } catch (...) {
        delete[] str;
        throw;
      }
      std::memcpy(bigger, str, size);
      delete[] str;
      str = bigger;
    }
    str[size] = symbol;
    ++size;
  }
  str[size] = '\0';
  return str;
}

int ovsyannikov::hasRepeats(const char * str)
{
  for (std::size_t i = 0; str[i] != '\0'; ++i) {
    for (std::size_t j = i + 1; str[j] != '\0'; ++j) {
      if (str[i] == str[j]) {
        return 1;
      }
    }
  }
  return 0;
}

char * ovsyannikov::excludeSymbols(const char * str, const char * excluded, char * result)
{
  std::size_t size = 0;
  for (std::size_t i = 0; str[i] != '\0'; ++i) {
    if (std::strchr(excluded, str[i]) == nullptr) {
      result[size] = str[i];
      ++size;
    }
  }
  result[size] = '\0';
  return result;
}

int main()
{
  char * input = nullptr;
  char * result = nullptr;
  try {
    input = ovsyannikov::readLine(std::cin);
    result = new char[std::strlen(input) + 1];
  } catch (const std::bad_alloc & e) {
    delete[] input;
    std::cerr << "not enough memory\n";
    return ovsyannikov::no_memory;
  }

  if (input[0] == '\0') {
    delete[] result;
    delete[] input;
    std::cerr << "input is empty\n";
    return ovsyannikov::empty_input;
  }

  const char * const second = "abc";
  std::cout << ovsyannikov::hasRepeats(input) << '\n';
  std::cout << ovsyannikov::excludeSymbols(input, second, result) << '\n';

  delete[] result;
  delete[] input;
}
