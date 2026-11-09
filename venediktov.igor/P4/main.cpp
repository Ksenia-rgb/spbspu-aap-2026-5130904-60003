#include <cctype>
#include <cstddef>
#include <iostream>
#include <new>

int readString(char **str_ptr, size_t *capacity_ptr) {
  int ch = 0;
  size_t length = 0;

  while ((ch = std::cin.get()) != '\n' && ch != EOF) {
    if (length + 2 > *capacity_ptr) {
      *capacity_ptr *= 2;
      char *const temp = *str_ptr;
      *str_ptr = new (std::nothrow) char[*capacity_ptr];

      if (*str_ptr == nullptr) {
        std::cerr << "Memory reallocation failed\n";
        delete[] temp;
        return 1;
      }

      for (size_t i = 0; i < length; i++) {
        (*str_ptr)[i] = temp[i];
      }
      delete[] temp;
    }
    (*str_ptr)[length] = static_cast<char>(ch);
    length++;
  }

  (*str_ptr)[length] = '\0';

  if (length == 0 && ch == EOF) {
    std::cerr << "Empty input\n";
    return 1;
  }

  return 0;
}

int appendDigits(char *dest, const char *src) {
  int dest_len = 0;
  while (dest[dest_len] != '\0') {
    dest_len++;
  }

  int i = 0;
  while (src[i] != '\0') {
    if (std::isdigit(static_cast<unsigned char>(src[i]))) {
      dest[dest_len] = src[i];
      dest_len++;
    }
    i++;
  }

  dest[dest_len] = '\0';

  return 0;
}

int hasRepeatedDigits(const char *str) {
  int counts[10];

  int i = 0;
  while (i < 10) {
    counts[i] = 0;
    i++;
  }

  i = 0;
  while (str[i] != '\0') {
    const unsigned char ch = static_cast<unsigned char>(str[i]);
    if (std::isdigit(ch)) {
      const int digit_index = ch - '0';

      counts[digit_index]++;

      if (counts[digit_index] > 1) {
        return 1;
      }
    }
    i++;
  }

  return 0;
}

int main() {
  const size_t initialCapacity = 50;
  size_t cap1 = initialCapacity;
  char *dest = new (std::nothrow) char[cap1];

  if (dest == nullptr) {
    std::cerr << "Memory allocation failed\n";
    return 1;
  }

  if (readString(&dest, &cap1) != 0) {
    delete[] dest;
    return 1;
  }

  const char *const src = "g1h2k";

  const int res2 = hasRepeatedDigits(dest);
  appendDigits(dest, src);

  std::cout << dest << "\n";
  std::cout << res2 << "\n";

  delete[] dest;
  return 0;
}