#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>

namespace glavan {

  int count_distinct_latin(const char *s) noexcept
  {
    if (s == nullptr) {
      return 0;
    }

    int seen[26] = {0};
    const char *p = s;
    while (*p != '\0') {
      char c = *p;
      if (std::isalpha((unsigned char)c)) {
        char low = (char)std::tolower((unsigned char)c);
        if (low >= 'a' && low <= 'z') {
          seen[low - 'a'] = 1;
        }
      }
      ++p;
    }

    int n = 0;
    int i = 0;
    while (i < 26) {
      n += seen[i];
      ++i;
    }
    return n;
  }

  int append_digits(const char *src, const char *second, char *dst, std::size_t dst_size) noexcept
  {
    if (src == nullptr || second == nullptr || dst == nullptr || dst_size == 0) {
      return -1;
    }

    std::size_t len = 0;
    const char *p = src;
    while (*p != '\0') {
      if (len + 1 >= dst_size) {
        return -1;
      }
      dst[len] = *p;
      ++len;
      ++p;
    }

    p = second;
    while (*p != '\0') {
      char c = *p;
      if (std::isdigit((unsigned char)c)) {
        if (len + 1 >= dst_size) {
          return -1;
        }
        dst[len] = c;
        ++len;
      }
      ++p;
    }

    dst[len] = '\0';
    return (int)len;
  }

  std::size_t count_digits(const char *s) noexcept
  {
    if (s == nullptr) {
      return 0;
    }
    std::size_t n = 0;
    const char *p = s;
    while (*p != '\0') {
      if (std::isdigit((unsigned char)*p)) {
        ++n;
      }
      ++p;
    }
    return n;
  }

}

int main()
{
  std::string input;
  try {
    if (!std::getline(std::cin, input)) {
      input.clear();
    }
  } catch (...) {
    std::cerr << "Error: not enough memory for input string\n";
    return 1;
  }

  const char *second = "g1h2k";

  std::cout << glavan::count_distinct_latin(input.c_str()) << '\n';

  std::size_t needed = input.size() + glavan::count_digits(second) + 1;
  std::vector< char > buf;
  try {
    buf.resize(needed);
  } catch (...) {
    std::cerr << "Error: not enough memory for result string\n";
    return 1;
  }

  if (glavan::append_digits(input.c_str(), second, buf.data(), buf.size()) < 0) {
    std::cerr << "Error: buffer for result is too small\n";
    return 1;
  }
  std::cout << buf.data() << '\n';

  return 0;
}
