#include <cctype>
#include <cstddef>
#include <iostream>
#include <new>

namespace bugaev {
  const int bad_string_code = 1;
  const std::size_t max_size = 100000;
  const int letters_count = 26;
  const int chars_count = 256;
  const int top_size = 3;

  char *shrSym(const char *source, char *result)
  {
    int present[letters_count] = {};
    for (const char *p = source; *p != '\0'; ++p) {
      if (std::isalpha(static_cast< unsigned char >(*p))) {
        ++present[std::tolower(static_cast< unsigned char >(*p)) - 'a'];
      }
    }
    int length = 0;
    for (int i = 0; i < letters_count; ++i) {
      if (present[i] == 0) {
        result[length] = static_cast< char >('a' + i);
        ++length;
      }
    }
    result[length] = '\0';
    return result;
  }

  char *frqTop(const char *source, char *result)
  {
    int counts[chars_count] = {};
    int picked[chars_count] = {};
    for (const char *p = source; *p != '\0'; ++p) {
      if (*p != ' ') {
        ++counts[static_cast< unsigned char >(*p)];
      }
    }
    for (int k = 0; k < top_size; ++k) {
      int best = -1;
      int best_count = 0;
      for (int i = 0; i < chars_count; ++i) {
        if (counts[i] > best_count) {
          best = i;
          best_count = counts[i];
        }
      }
      if (best >= 0) {
        picked[best] = 1;
        counts[best] = 0;
      }
    }
    int length = 0;
    for (int i = 0; i < chars_count; ++i) {
      if (picked[i] == 1) {
        result[length] = static_cast< char >(i);
        ++length;
      }
    }
    result[length] = '\0';
    return result;
  }
}

int main()
{
  char *line = nullptr;
  try {
    line = new char[bugaev::max_size];
  } catch (const std::bad_alloc &) {
    std::cerr << "Error: not enough memory\n";
    return bugaev::bad_string_code;
  }

  std::size_t length = 0;
  char symbol = '\0';
  while (std::cin.get(symbol) && (symbol != '\n')) {
    if (length + 1 >= bugaev::max_size) {
      std::cerr << "Error: string is too long\n";
      delete[] line;
      return bugaev::bad_string_code;
    }
    line[length] = symbol;
    ++length;
  }
  line[length] = '\0';
  if (length == 0) {
    std::cerr << "Error: empty string\n";
    delete[] line;
    return bugaev::bad_string_code;
  }

  char missing[bugaev::letters_count + 1] = {};
  char frequent[bugaev::top_size + 1] = {};
  std::cout << bugaev::shrSym(line, missing) << '\n';
  std::cout << bugaev::frqTop(line, frequent) << '\n';
  delete[] line;
  return 0;
}
