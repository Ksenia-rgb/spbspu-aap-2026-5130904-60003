#include <iostream>
#include <limits>
#include <new>

namespace polohov {
char *getString(long long &curr_size) {
  long long size = 10;

  char *str = new char[size];
  char ch = '\0';

  while (std::cin.get(ch) && ch != '\n') {
    if (curr_size == size - 1) {
      try {
        if (size > std::numeric_limits<long long>::max() / 2) {
          throw std::bad_alloc();
        }

        size *= 2;

        char *const temp = new char[size];

        for (long long i = 0; i < curr_size; ++i) {
          temp[i] = str[i];
        }

        delete[] str;
        str = temp;
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
    }

    str[curr_size++] = ch;
  }

  str[curr_size] = '\0';

  return str;
}

int replaceSymbol(const char *str, char *res, char old_char, char new_char) {
  if (str == nullptr || res == nullptr) {
    return 1;
  }

  long long i = 0;

  for (; str[i] != '\0'; ++i) {
    if (str[i] == old_char) {
      res[i] = new_char;
    } else {
      res[i] = str[i];
    }
  }

  res[i] = '\0';
  return 0;
}

int findSame(const char *old_str, const char *new_str) {
  if (old_str == nullptr || new_str == nullptr) {
    return 1;
  }

  for (long long i = 0; old_str[i] != '\0'; ++i) {
    for (long long j = 0; new_str[j] != '\0'; ++j) {
      if (old_str[i] == new_str[j]) {
        return 2;
      }
    }
  }

  return 0;
}
}
int main() {
  char *str = nullptr;
  char *res = nullptr;

  try {
    long long curr_size = 0;

    str = polohov::getString(curr_size);

    if (curr_size == 0 && std::cin.eof()) {
      delete[] str;
      str = nullptr;

      std::cerr << "Error: No input provided.\n";
      return 1;
    }

    res = new char[curr_size + 1];

    const char old_char = 'a';
    const char new_char = 'b';

    const int replace_result =
        polohov::replaceSymbol(str, res, old_char, new_char);

    if (replace_result == 1) {
      std::cerr << "Error: Null pointer encountered in replaceSymbol.\n";
      delete[] str;
      delete[] res;
      return 1;
    }

    const int find_result = polohov::findSame(str, "abc");

    if (find_result == 1) {
      std::cerr << "Error: Null pointer encountered in findSame.\n";
      delete[] str;
      delete[] res;
      return 1;
    } else if (find_result == 2) {
      std::cout << "There is at least one common character.\n";
    } else {
      std::cout << "There are no common characters.\n";
    }

    std::cout << "Original string: " << str << "\n";
    std::cout << "Modified string: " << res << "\n";

    delete[] str;
    delete[] res;

    return 0;
  } catch (const std::bad_alloc &e) {
    delete[] str;
    delete[] res;

    std::cerr << "Memory allocation failed: " << e.what() << "\n";
    return 1;
  }
}
