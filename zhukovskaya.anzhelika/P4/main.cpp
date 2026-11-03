#include <iostream>
#include <cstddef>
#include <new>
#include <cstring>
#include <stdexcept>
namespace zhukovskaya {
  char* allChars(char* res, char* str1, const char* str2) noexcept {
    const size_t alph_size = 26;
    int alph[alph_size]{};
    for (size_t i = 0; str1[i] != '\0'; ++i) {
      if (isalpha(str1[i])) {
        const int low_regist = tolower(str1[i]);
        res[low_regist - int('a')] = 1;
      }
    }
    for (size_t i = 0; str2[i] != '\0'; ++i) {
      if (isalpha(str2[i])) {
        const int low_regist = tolower(str2[i]);
        res[low_regist - int('a')] = 1;
      }
    }
    size_t cnt_index = 0;
    for (size_t i = 0; i < alph_size; ++i) {
      if (res[i] != 0) {
        res[cnt_index] = char('a' + i);
        cnt_index++;
      }
    }
    res[cnt_index] = '\0';
    return res;
  }

  int sameChars(char* str1, const char* str2) noexcept {
    int flag = 0;
    for (size_t i = 0; str1[i] != '\0'; ++i) {
      for (size_t j = 0; str2[j] != '\0'; ++j) {
        if (str1[i] == str2[j]) {
          flag = 1;
          return flag;
          break;
        }
      }
    }
    return flag;
  }
  char* expandMem(char* old_memory, size_t old_size, size_t new_size) {
    char* new_memory = new char[new_size];
    for (size_t i = 0; i < old_size; ++i) {
      new_memory[i] = old_memory[i];
    }
    delete[] old_memory;
    return new_memory;
  }
  char* readStr() {
    //size_t start_size = 20;
    size_t step = 10;
    size_t size = 0;
    size_t memory_size = 20;
    char* memory = new char[memory_size];
    std::cout << "enter your string: \n";

    while(true) {
      char ch;
      if (!std::cin.get(ch) || (ch == '\n')) {
        break;
      }
      if (size + 1 == memory_size) {
        try {
          memory = expandMem(memory, size, memory_size + step);
        }
        catch (const std::bad_alloc& e) {
          delete[] memory;
          throw;
        }
        memory_size += step;
      }
      memory[size] = ch;
      size++;
    }
    memory[size] = '\0';
    return memory;
  }
}

int main() {
  char* in_str1 = nullptr;
  char* for_res = nullptr;

  try {
    in_str1 = zhukovskaya::readStr();

    const char* str2 = "ajdbe_b";
    const size_t alph_num = 26;
    for_res = new char[alph_num + 1];

    zhukovskaya::allChars(for_res, in_str1, str2);
    int res_same_chars = zhukovskaya::sameChars(in_str1, str2);

    std::cout << "all symbols in these strings: " << for_res;
    std::cout << "\n";
    std::cout << "result for the check of the same symbols: " << res_same_chars;
    std::cout << "\n";

    delete[] in_str1;
    delete[] for_res;
  }

  catch (const std::bad_alloc& e) {
    delete[] in_str1;
    delete[] for_res;
    std::cerr << "memory allocation error" << "\n";
    return 1;
  }
  return 0;
}
