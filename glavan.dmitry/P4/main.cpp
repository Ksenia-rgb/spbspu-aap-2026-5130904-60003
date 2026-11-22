#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>

namespace glavan {

  const int kAlphabetSize = 26;

  int countDistinctLatin(const char *s) noexcept
  {
    if (s == nullptr) {
      return 0;
    }

    int seen[kAlphabetSize] = {0};
    const char *p = s;
    while (*p != '\0') {
      const char c = *p;
      if (std::isalpha(static_cast< unsigned char >(c))) {
        const char low = static_cast< char >(std::tolower(static_cast< unsigned char >(c)));
        if (low >= 'a' && low <= 'z') {
          seen[low - 'a'] = 1;
        }
      }
      ++p;
    }

    int n = 0;
    int i = 0;
    while (i < kAlphabetSize) {
      n += seen[i];
      ++i;
    }
    return n;
  }

  int appendDigits(const char *src, const char *second, char *dst, std::size_t dst_size) noexcept
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
      const char c = *p;
      if (std::isdigit(static_cast< unsigned char >(c))) {
        if (len + 1 >= dst_size) {
          return -1;
        }
        dst[len] = c;
        ++len;
      }
      ++p;
    }

    dst[len] = '\0';
    return static_cast< int >(len);
  }

  std::size_t countDigits(const char *s) noexcept
  {
    if (s == nullptr) {
      return 0;
    }
    std::size_t n = 0;
    const char *p = s;
    while (*p != '\0') {
      if (std::isdigit(static_cast< unsigned char >(*p))) {
        ++n;
      }
      ++p;
    }
    return n;
  }

} // namespace glavan

int main()
{
  std::string input;
  try {
    if (!std::getline(std::cin, input)) {
      std::cerr << "Error: failed to read input string\n";
      return 1;
    }
  } catch (...) {
    std::cerr << "Error: not enough memory for input string\n";
    return 1;
  }

  const char *const second = "g1h2k";

  std::cout << glavan::countDistinctLatin(input.c_str()) << '\n';

  const std::size_t needed = input.size() + glavan::countDigits(second) + 1;
  std::vector< char > buf;
  try {
    buf.resize(needed);
  } catch (...) {
    std::cerr << "Error: not enough memory for result string\n";
    return 1;
  }

  if (glavan::appendDigits(input.c_str(), second, buf.data(), buf.size()) < 0) {
    std::cerr << "Error: buffer for result is too small\n";
    return 1;
  }
  std::cout << buf.data() << '\n';

  return 0;
}
