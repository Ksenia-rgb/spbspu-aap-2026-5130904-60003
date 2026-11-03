#include <cctype>
#include <cstddef>
#include <iostream>
#include <new>

namespace zhukovskaya {
  char* allChars(char* res, const char* str1, const char* str2) noexcept
  {
    const std::size_t alph_size = 26;
    int alph[alph_size] = {0};

    for (std::size_t i = 0; str1[i] != '\0'; ++i) {
      const unsigned char ch = static_cast< unsigned char >(str1[i]);
      if (std::isalpha(ch)) {
        const int low_regist = std::tolower(ch);
        alph[low_regist - 'a'] = 1;
      }
    }

    for (std::size_t i = 0; str2[i] != '\0'; ++i) {
      const unsigned char ch = static_cast< unsigned char >(str2[i]);
      if (std::isalpha(ch)) {
        const int low_regist = std::tolower(ch);
        alph[low_regist - 'a'] = 1;
      }
    }

    std::size_t cnt_index = 0;
    for (std::size_t i = 0; i < alph_size; ++i) {
      if (alph[i] != 0) {
        res[cnt_index] = static_cast< char >('a' + i);
        cnt_index++;
      }
    }
    res[cnt_index] = '\0';
    return res;
  }

  int sameChars(const char* str1, const char* str2) noexcept
  {
    for (std::size_t i = 0; str1[i] != '\0'; ++i) {
      for (std::size_t j = 0; str2[j] != '\0'; ++j) {
        if (str1[i] == str2[j]) {
          return 1;
        }
      }
    }
    return 0;
  }

  char* expandMem(char* old_memory, const std::size_t old_size, const std::size_t new_size)
  {
    char* new_memory = new char[new_size];
    for (std::size_t i = 0; i < old_size; ++i) {
      new_memory[i] = old_memory[i];
    }
    delete[] old_memory;
    return new_memory;
  }

  char* readStr()
  {
    const std::size_t step = 10;
    const std::size_t initial_capacity = 20;
    std::size_t size = 0;
    std::size_t memory_size = initial_capacity;
    char* memory = new char[memory_size];

    while (true) {
      char ch = '\0';
      if (!std::cin.get(ch) || (ch == '\n')) {
        break;
      }
      if (size + 1 == memory_size) {
        try {
          memory = expandMem(memory, size, memory_size + step);
        } catch (const std::bad_alloc&) {
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

int main()
{
  char* in_str1 = nullptr;
  char* for_res = nullptr;

  try {
    in_str1 = zhukovskaya::readStr();

    const char* const str2_lat = "def_ghk";
    const char* const str2_same = "abs";
    const std::size_t alph_num = 26;
    for_res = new char[alph_num + 1];

    zhukovskaya::allChars(for_res, in_str1, str2_lat);
    const int res_same_chars = zhukovskaya::sameChars(in_str1, str2_same);

    std::cout << for_res << "\n";
    std::cout << res_same_chars << "\n";

    delete[] in_str1;
    delete[] for_res;
  } catch (const std::bad_alloc&) {
    delete[] in_str1;
    delete[] for_res;
    std::cerr << "memory allocation error\n";
    return 1;
  }

  return 0;
}
