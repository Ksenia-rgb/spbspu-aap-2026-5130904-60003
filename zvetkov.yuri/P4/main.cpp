#include <iostream>
#include <cstring>
#include <cctype>

namespace zvetkov
{
  char* pwie()
  {
    int pwie_size = 0;
    char* pwie = new char[1];
    char symbol = '\0';

    while ((std::cin.get(symbol)) && (symbol != '\n'))
    {
      pwie_size++;
      char* const new_pwie = new char[pwie_size + 1];

      for (int i = 0; i < pwie_size - 1; i++)
      {
        new_pwie[i] = pwie[i];
      }

      new_pwie[pwie_size - 1] = symbol;
      delete[] pwie;
      pwie = new_pwie;
    }

    if (pwie_size == 0)
    {
      delete[] pwie;
      throw std::runtime_error("What? Cat got your tongue?");
    }

    pwie[pwie_size] = '\0';

    return pwie;
  }

  void replaceSymbol(const char* input_string, char* output_string, char from, char to)
  {
    for (int i = 0; input_string[i] != '\0'; i++)
    {
      if (input_string[i] == from)
      {
        output_string[i] = to;
      }
      else
      {
        output_string[i] = input_string[i];
      }
    }

    output_string[strlen(input_string)] = '\0';
  }

  int found(const char* input_string, const char* template_string)
  {
    for (int i = 0; input_string[i] != '\0'; i++)
    {
      for (int j = 0; template_string[j] != '\0'; j++)
      {
        if (input_string[i] == template_string[j])
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
  try
  {
    char* const input_string = zvetkov::pwie();
    const char* const template_string = "abs";
    char* const output_string = new char[std::strlen(input_string) + 1];

    zvetkov::replaceSymbol(input_string, output_string, 'c', 'b');
    std::cout << output_string << "\n";

    const int result = zvetkov::found(input_string, template_string);
    std::cout << result << "\n";

    delete[] input_string;
    delete[] output_string;
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "No memory?\n";
    return 1;
  }

  return 0;
}
