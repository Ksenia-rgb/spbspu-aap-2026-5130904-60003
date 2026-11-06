#include <cctype>
#include <iostream>
#include <stdexcept>
namespace andreikovets
{
  char* readString(size_t& cur_size)
  {
    size_t max_size = 8;
    char* str = nullptr;
    str = new char[max_size];
    char ch = '\0';
    while (std::cin.get(ch) && ch != '\n') {
      if (cur_size + 1 == max_size) {
        max_size *= 2;
        char* temp_ptr = nullptr;
        try {
          temp_ptr = new char[max_size];
        } catch (...) {
          delete[] str;
          throw std::runtime_error("Cannot get memory");
        }
        for (size_t i = 0; i < cur_size; ++i) {
          temp_ptr[i] = str[i];
        }
        delete[] str;
        str = temp_ptr;
      }
      str[cur_size++] = ch;
    }
    str[cur_size] = '\0';
    return str;
  }

  void deleteLetters(const char* init_str, char* num_str)
  {
    int el = 0;
    for (int i = 0; init_str[i] != '\0'; ++i) {
      if (!std::isalpha(init_str[i])) {
        num_str[el++] = init_str[i];
      }
    }
    num_str[el] = '\0';
  }

  void replaceSymbol(const char* init_str, char* repl_str,
                     const char target_char, const char repl_char)
  {
    int i = 0;
    for (; init_str[i] != '\0'; ++i) {
      if (init_str[i] == target_char) {
        repl_str[i] = repl_char;
      } else {
        repl_str[i] = init_str[i];
      }
    }
    repl_str[i] = '\0';
  }
}

int main()
{
  char* init_string = nullptr;
  char* num_string = nullptr;
  char* replace_string = nullptr;
  size_t size = 0;
  try {
    init_string = andreikovets::readString(size);
    if (size == 0) {
      throw std::logic_error("Empty input");
    }
    num_string = new char[size + 1];
    replace_string = new char[size + 1];
    andreikovets::deleteLetters(init_string, num_string);
    std::cout << num_string << "\n";
    andreikovets::replaceSymbol(init_string, replace_string, 'a', 'b');
    std::cout << replace_string << "\n";
  } catch (const std::exception& e) {
    delete[] init_string;
    delete[] num_string;
    delete[] replace_string;
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  }
  delete[] num_string;
  delete[] init_string;
  delete[] replace_string;
  return 0;
}
