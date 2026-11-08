#include <iostream>
#include <cctype>
#include <cstddef>

namespace boretskii {
  const size_t max_size_comb = 2048;
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
    char combined[max_size_comb];
    int index_comb = 0;
    int index_res = 0;
    for (int i = 0; first[i] != '\0'; i++) {
      combined[index_comb] = first[i];
      ++index_comb;
    }
    for (int j = 0; second[j] != '\0'; j++) {
      combined[index_comb] = second[j];
      ++index_comb;
    }
    combined[index_comb] = '\0';
    for (char letter = 'a'; letter <= 'z'; letter++) {
      for (int h = 0; combined[h] != '\0'; h++) {
        if (std::tolower(static_cast<unsigned char>(combined[h])) == letter) {
          result[index_res] = letter;
          ++index_res;
          break;
        }
      }
    }
    result[index_res] = '\0';
    return result;
  }
}

int main()
{
  const size_t max_size = 1024;
  char input_str[max_size];
  std::cin.getline(input_str, max_size);
  if (!std::cin) {
    std::cerr << "Error reading string\n";
    return 1;
  }
  char res_buffer[max_size];
  const char *const second_string = "ahgvwddc2165";
  std::cout << boretskii::identicalValues(input_str, second_string) << "\n";
  std::cout << boretskii::latTwo(input_str, second_string, res_buffer) << "\n";
  return 0;
}
