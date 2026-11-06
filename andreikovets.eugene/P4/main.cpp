#include <cctype>
#include <iostream>
#include <stdexcept>
namespace andreikovets
{
  char* readString(size_t& curSize)
  {
    size_t maxSize = 8;
    char* str = nullptr;
    str = new char[maxSize];
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
      if (curSize + 1 == maxSize) {
        maxSize *= 2;
        char* tempPtr = nullptr;
        try {
          tempPtr = new char[maxSize];
        } catch (...) {
          delete[] str;
          throw std::runtime_error("Cannot get memory");
        }
        for (size_t i = 0; i < curSize; ++i) {
          tempPtr[i] = str[i];
        }
        delete[] str;
        str = tempPtr;
      }
      str[curSize++] = ch;
    }
    str[curSize] = '\0';
    return str;
  }

  void deleteLetters(const char* initStr, char* numStr)
  {
    int el = 0;
    for (int i = 0; initStr[i] != '\0'; ++i) {
      if (!std::isalpha(initStr[i])) {
        numStr[el++] = initStr[i];
      }
    }
    numStr[el] = '\0';
  }

  void replaceSymbol(const char* initStr, char* replStr, const char targetChar,
                     const char replChar)
  {
    int i = 0;
    for (; initStr[i] != '\0'; ++i) {
      if (initStr[i] == targetChar) {
        replStr[i] = replChar;
      } else {
        replStr[i] = initStr[i];
      }
    }
    replStr[i] = '\0';
  }
}

int main()
{
  char* initString = nullptr;
  char* numString = nullptr;
  char* replaceString = nullptr;
  size_t size = 0;
  try {
    initString = andreikovets::readString(size);
    if (size == 0) {
      throw std::logic_error("Empty input");
    }
    numString = new char[size + 1];
    replaceString = new char[size + 1];
    andreikovets::deleteLetters(initString, numString);
    std::cout << numString << "\n";
    andreikovets::replaceSymbol(initString, replaceString, 'a', 'b');
    std::cout << replaceString << "\n";
  } catch (const std::exception& e) {
    delete[] initString;
    delete[] numString;
    delete[] replaceString;
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  }
  delete[] numString;
  delete[] initString;
  delete[] replaceString;
  return 0;
}
