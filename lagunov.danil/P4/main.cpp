#include <iostream>
#include <cstring>

namespace lagunov
{
  const size_t buffer_size = 8;

  void repeatingSymbols(const char* input, size_t size, char* result)
  {
    size_t index = 0;
    for (size_t i = 0; i < size; ++i)
    {
      bool flag = false;
      for (size_t k = 0; k < index; ++k)
      {
        if (input[i] == result[k])
        {
          flag = true;
          break;
        }
      }
      if (flag)
      {
        continue;
      }
      for (size_t j = i + 1; j < size; ++j)
      {
        if (input[i] == input[j])
        {
          result[index] = input[i];
          ++index;
          break;
        }
      }
    }
    result[index] = '\0';
  }

  int repeatingDigits(char* input, size_t size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      for (size_t j = i + 1; j < size; ++j)
      {
        if (input[i] == input[j] && std::isdigit(static_cast< unsigned char >(input[i])))
        {
          return 1;
        }
      }
    }
    return 0;
  }
}

int main()
{
  char* input = nullptr;
  char* first_result = nullptr;
  size_t size = 0;
  size_t buffer_capacity = lagunov::buffer_size;
  try
  {
    input = new char[buffer_capacity];
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "ERROR: cannot allocate memory\n";
    return 1;
  }

  char symbol = '\0';
  while (std::cin.get(symbol) && symbol != '\n')
  {
    if (size + 1 >= buffer_capacity)
    {
      buffer_capacity *= 2;
      char* temp_buffer = nullptr;
      try
      {
        temp_buffer = new char[buffer_capacity];
      }
      catch (const std::bad_alloc& e)
      {
        delete[] input;
        return 1;
      }
      input[size] = '\0';
      std::strcpy(temp_buffer, input);
      delete[] input;
      input = temp_buffer;
    }

    input[size] = symbol;
    ++size;
  }
  input[size] = '\0';
  if (size == 0)
  {
    std::cerr << "ERROR: empty input\n";
    delete[] input;
    return 1;
  }

  try
  {
    first_result = new char[size + 1];
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "ERROR: cannot allocate memory\n";
    delete[] input;
    return 1;
  }

  lagunov::repeatingSymbols(input, size, first_result);
  std::cout << first_result << '\n';
  std::cout << lagunov::repeatingDigits(input, size) << '\n';

  delete[] input;
  delete[] first_result;
  return 0;
}
