#include <iostream>
#include <cctype>
#include <cstddef>

namespace boretskii
{
  const size_t maxSizeComb = 2048;
  int identicalValues(const char *first, const char *second)
  {
    for (int i = 0; first[i] != '\0'; i++) {
      for (int j = 0; second[j] != '\0'; j++) {
        if (first[i] == second[j]) {
          return 1;
        }
      }
    }
    return 0;
  }
  char *latTwo(const char *first, const char *second, char *result)
  {
    char combined[maxSizeComb];
    int indexComb = 0;
    int indexRes = 0;
    for (int i = 0; first[i] != '\0'; i++) {
      combined[indexComb] = first[i];
      ++indexComb;
    }
    for (int j = 0; second[j] != '\0'; j++) {
      combined[indexComb] = second[j];
      ++indexComb;
    }
    combined[indexComb] = '\0';
    for (char letter = 'a'; letter <= 'z'; letter++) {
      for (int h = 0; combined[h] != '\0'; h++) {
        if (std::tolower(static_cast<unsigned char>(combined[h])) == letter) {
          result[indexRes] = letter;
          ++indexRes;
          break;
        }
      }
    }
    result[indexRes] = '\0';
    return result;
  }
}
int main()
{
  const size_t maxSize = 1024;
  char inputStr[maxSize];
  std::cin.getline(inputStr, maxSize);
  if (!std::cin) {
    std::cerr << "Error reading string\n";
    return 1;
  }
  char resBuffer[maxSize];
  const char *secondString = "ahgvwddc2165";
  std::cout << boretskii::identicalValues(inputStr, secondString) << "\n";
  std::cout << boretskii::latTwo(inputStr, secondString, resBuffer) << "\n";
  return 0;
}
