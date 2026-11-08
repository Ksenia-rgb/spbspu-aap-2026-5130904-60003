#include <iostream>
#include <cstring>
#include <cstddef>
#include <new>

namespace vakulov {
  class MyString {
  public:
    MyString(std::size_t capacity);
    MyString(const MyString &) = delete;
    MyString &operator=(const MyString &) = delete;
    ~MyString();

    void append(char symbol);
    char *data();
    std::size_t size() const;

  private:
    char *data_;
    std::size_t size_;
    std::size_t capacity_;
  };

  char *removeFromSecond(const char *source, const char *excluded, char *result);
  char *removeGlas(const char *source, char *result);
}

vakulov::MyString::MyString(std::size_t capacity):
  data_(new char[capacity]),
  size_(0),
  capacity_(capacity)
{
  data_[0] = '\0';
}

vakulov::MyString::~MyString()
{
  delete[] data_;
}

void vakulov::MyString::append(char symbol)
{
  if (size_ + 1 >= capacity_) {
    const std::size_t new_capacity = capacity_ * 2;
    char *new_data = new char[new_capacity];

    for (std::size_t i = 0; i <= size_; ++i) {
      new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }

  data_[size_] = symbol;
  ++size_;
  data_[size_] = '\0';
}

char *vakulov::MyString::data()
{
  return data_;
}

std::size_t vakulov::MyString::size() const
{
  return size_;
}

char *vakulov::removeFromSecond(const char *source, const char *excluded, char *result)
{
  std::size_t j = 0;

  for (std::size_t i = 0; source[i] != '\0'; ++i) {
    if (std::strchr(excluded, source[i]) == nullptr) {
      result[j] = source[i];
      ++j;
    }
  }

  result[j] = '\0';
  return result;
}

char *vakulov::removeGlas(const char *source, char *result)
{
  return vakulov::removeFromSecond(source, "aeiouAEIOU", result);
}

int main()
{
  try {
    vakulov::MyString source(1);
    char symbol = '\0';

    while (std::cin.get(symbol)) {
      if (symbol == '\n') {
        break;
      }
      source.append(symbol);
    }

    if (std::cin.bad()) {
      std::cerr << "Input error\n";
      return 2;
    }

    vakulov::MyString result15(source.size() + 1);
    vakulov::MyString result18(source.size() + 1);

    vakulov::removeFromSecond(source.data(), "abc", result15.data());
    vakulov::removeGlas(source.data(), result18.data());

    std::cout << result15.data() << '\n';
    std::cout << result18.data() << '\n';

    if (!std::cout) {
      std::cerr << "Output error\n";
      return 2;
    }

    return 0;
  } catch (const std::bad_alloc &) {
    std::cerr << "Memory alloc error\n";
    return 1;
  }
}
