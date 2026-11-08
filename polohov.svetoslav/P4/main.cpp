#include <iostream>

namespace polohov {

  char* getString(long long& curr_size) {
    long long size = 10;

    char* str = new char[size];
    char ch;

    while (std::cin.get(ch) && ch != '\n') {
      if (curr_size == size - 1) {
        size *= 2;

        try {
          char* temp = new char[size];

          for (int i = 0; i < curr_size; ++i) {
            temp[i] = str[i];
          }

          delete[] str;
          str = temp;
        }
        catch (const std::bad_alloc&) {
          delete[] str;
          throw;
        }
      }

      str[curr_size++] = ch;
    }

    str[curr_size] = '\0';

    return str;
  }

  int replaceSymbol(const char* str, char* res, char oldChar, char newChar) {
    int i = 0;

    if (str == nullptr || res == nullptr) {
      return 1;
    }

    for (; str[i] != '\0'; ++i) {
      if (str[i] == oldChar) {
        res[i] = newChar;
      }
      else {
        res[i] = str[i];
      }
    }

    res[i] = '\0';
    return 0;
  }

  int findSame(const char* oldStr, const char* newStr) {
    if (oldStr == nullptr || newStr == nullptr) {
      return 1;
    }

    for (int i = 0; oldStr[i] != '\0'; i++) {
      for (int j = 0; newStr[j] != '\0'; j++) {
        if (oldStr[i] == newStr[j]) {
          return 2;
        }
      }
    }

    return 0;
  }

}

int main() {
  char* str = nullptr;
  char* res = nullptr;

  try {
    long long curr_size = 0;
    str = polohov::getString(curr_size);
    if (std::cin.eof() && curr_size == 0) {
    delete[] str;
    str = nullptr;
    std::cerr << "Error: No input provided.\n";
    return 1;
  }
    res = new char[curr_size + 1];

    char oldChar = 'a';
    char newChar = 'b';


    int replaceResult = polohov::replaceSymbol(str, res, oldChar, newChar);

    if (replaceResult == 1) {
      std::cerr << "Error: Null pointer encountered in replaceSymbol." << "\n";
      delete[] str;
      delete[] res;
      return 1;
    }

    int findResult = polohov::findSame(str, "abc");

    if (findResult == 1) {
      std::cerr << "Error: Null pointer encountered in findSame." << "\n";
      delete[] str;
      delete[] res;
      return 1;
    }
    else if (findResult == 2) {
      std::cout << "There are same symbols" << "\n";
    }
    else {
      std::cout << "There arent same symbols" << "\n";
    }

    std::cout << "Original string: " << str << "\n";
    std::cout << "Modified string: " << res << "\n";

    delete[] str;
    delete[] res;

    return 0;
  }
  catch (const std::bad_alloc& e) {
    delete[] str;
    delete[] res;

    std::cerr << "Memory allocation failed: " << e.what() << "\n";
    return 1;
  }
}
