#include <cctype>
#include <cstring>
#include <iostream>
#include <new>
namespace kudrenok
{
  const int successCode = 0;
  const int ErrorCode = 1;
  int yesChar(const char* str, char c)
  {
    while (*str != '\0')
    {
      if (*str == c)
      {
        return 1;
      }
      str++;
    }
    return 0;
  }
  int isGlasnai(char c)
  {
    const char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u' || lower == 'y');
  }
  char* findUncommonSym(const char* str1, const char* str2, char* output)
  {
    char* const start = output;
    const char* p1 = str1;
    while (*p1 != '\0')
    {
      if (!yesChar(str2, *p1) && !yesChar(start, *p1))
      {
        *output = *p1;
        output++;
      }
      p1++;
    }

    const char* p2 = str2;
    while (*p2 != '\0')
    {
      if (!yesChar(str1, *p2) && !yesChar(start, *p2))
      {
        *output = *p2;
        output++;
      }
      p2++;
    }
    *output = '\0';
    return start;
  }
  char* removeGlasnai(const char* src, char* output)
  {
    char* const start = output;
    while (*src != '\0')
    {
      if (!isGlasnai(*src))
      {
        *output = *src;
        output++;
      }
        src++;
    }
      *output = '\0';
      return start;
  }
}
int main()
{
  char* input_str = nullptr;
  int volume1 = 0;
  int length = 0;
  try
  {
    while (true)
    {
      const int ch = std::cin.get();
      if (ch == '\n' || ch == EOF)
      {
        break;
      }
      if (length + 1 >= volume1)
      {
         const int newVolume1 = volume1 + 2;
         char* const new_buffer = new char[newVolume1]();
         for (int i = 0; i < length; ++i)
         {
            new_buffer[i] = input_str[i];
         }
           delete[] input_str;
           input_str = new_buffer;
           volume1 = newVolume1;
        }
          input_str[length] = static_cast<char>(ch);
          length++;
    }
    if (length == 0)
    {
      std::cerr << "Error: Empty input\n";
      delete[] input_str;
      return kudrenok::ErrorCode;
    }
    if (input_str != nullptr)
    {
      input_str[length]='\0';
    }
      const char* const second_str = "abc_ef";
      char* const res_variant18 = new char[length + 1]();
      char* const res_variant5 = new char[length + std::strlen(second_str) + 1]();
      kudrenok::findUncommonSym(input_str, second_str, res_variant5);
      kudrenok::removeGlasnai(input_str, res_variant18);
      std::cout << res_variant5 << std::endl;
      std::cout << res_variant18 << std::endl;
      delete[] input_str;
      delete[] res_variant5;
      delete[] res_variant18;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: Memory allocation failed\n";
    delete[] input_str;
    return kudrenok::ErrorCode;
  }
    return kudrenok::successCode;
}
