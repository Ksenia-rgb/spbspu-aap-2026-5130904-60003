#include <cctype>
#include <cstddef>
#include <new>
#include <cstring>
#include <iostream>

namespace somov {
  const size_t MAXSIZE = 1000000000;
  const int correct_exit = 0;
  const int incorrect_string = 1;
  const int internal_error = 2;
  const char* const str2 = "def_";
  const size_t len2 = std::strlen(str2);

  char* toLowerCase(const char* str, char* lower_str, size_t len)
  {
    for (size_t i = 0; i < len; ++i) {
      lower_str[i] = static_cast< char >(std::tolower(str[i]));
    }
    lower_str[len] = '\0';
    return lower_str;
  }

  char* combineStrings(const char* str1, const char* str2, char* comb_str, size_t len1, size_t len2)
  {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while (len1 > i || len2 > j) {
      if (len1 > i) {
        comb_str[k++] = str1[i++];
      }
      if (len2 > j) {
        comb_str[k++] = str2[j++];
      }
    }
    comb_str[k] = '\0';
    return comb_str;
  }
}

int main()
{
  char* str = nullptr;
  char* lower_str = nullptr;
  char* comb_str = nullptr;

  try {
    str = new char[somov::MAXSIZE];
    lower_str = new char[somov::MAXSIZE];
    comb_str = new char[somov::MAXSIZE + somov::len2];
  }

  catch (const std::bad_alloc&) {
    std::cerr << "Not enough memory!\n";
    delete[] str;
    delete[] lower_str;
    delete[] comb_str;
    return somov::internal_error;
  }

  size_t len = 0;
  char c = 0;

  while (std::cin.get(c) && c != '\n') {
    if (len + 1 >= somov::MAXSIZE) {
      std::cerr << "Sorry, your string is out of range!\n";
      delete[] str;
      delete[] lower_str;
      delete[] comb_str;
      return somov::incorrect_string;
    }
    str[len++] = c;
  }

  if (len == 0) {
    std::cerr << "No input!\n";
    delete[] str;
    delete[] lower_str;
    delete[] comb_str;
    return somov::incorrect_string;
  }

  str[len] = '\0';

  somov::toLowerCase(str, lower_str, len);
  std::cout << "String in lower case: " << lower_str << '\n';

  somov::combineStrings(str, somov::str2, comb_str, len, somov::len2);
  std::cout << "Combination of string1 and string2: " << comb_str << '\n';

  delete[] str;
  delete[] lower_str;
  delete[] comb_str;
  return somov::correct_exit;
}
