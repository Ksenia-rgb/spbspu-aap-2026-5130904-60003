#include <cctype>
#include <iostream>
#include <new>
#include <string>

namespace binkovsky {
  int combineStrings(const char *a, const char *b, char *result)
  {
    int i = 0;
    int j = 0;
    int k = 0;

    while (a[i] != '\0' || b[j] != '\0') {
      if (a[i] != '\0') {
        result[k++] = a[i++];
      }

      if (b[j] != '\0') {
        result[k++] = b[j++];
      }
    }

    result[k] = '\0';
    return k;
  }

  int removeExtraSpaces(const char *str, char *result)
  {
    int i = 0;
    int j = 0;

    while (str[i] != '\0' && std::isspace(static_cast< unsigned char >(str[i]))) {
      ++i;
    }

    while (str[i] != '\0') {
      if (!std::isspace(static_cast< unsigned char >(str[i]))) {
        result[j++] = str[i++];
      } else {
        result[j++] = ' ';

        while (str[i] != '\0' && std::isspace(static_cast< unsigned char >(str[i]))) {
          ++i;
        }
      }
    }

    if (j > 0 && result[j - 1] == ' ') {
      --j;
    }

    result[j] = '\0';
    return j;
  }

  int run()
  {
    try {
      std::string first;
      std::string second;

      if (!std::getline(std::cin, first) || !std::getline(std::cin, second)) {
        std::cerr << "Error: input failed\n";
        return 1;
      }

      char *combined = new (std::nothrow) char[first.size() + second.size() + 1];

      char *cleaned = new (std::nothrow) char[first.size() + 1];

      if (combined == nullptr || cleaned == nullptr) {
        delete[] combined;
        delete[] cleaned;
        std::cerr << "Error: memory allocation failed\n";
        return 1;
      }

      combineStrings(first.c_str(), second.c_str(), combined);
      removeExtraSpaces(first.c_str(), cleaned);

      std::cout << combined << '\n';
      std::cout << cleaned << '\n';

      delete[] combined;
      delete[] cleaned;
    } catch (const std::bad_alloc &) {
      std::cerr << "Error: memory allocation failed\n";
      return 1;
    }

    return 0;
  }

}
int main()
{
  return binkovsky::run();
}
