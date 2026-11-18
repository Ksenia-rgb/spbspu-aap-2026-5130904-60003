#include <iostream>

namespace ershov
{
  class Letter
  {
  public:
    char name;
    int count;

    Letter():
      name(0),
      count(0)
    {}
  };

  void findMissing(Letter* line)
  {
    for (char s = 'a'; s <= 'z'; s++)
    {
      const Letter* p = line;

      while (p->name != '\0' && p->name != s)
      {
        p++;
      }

      if (p->name == '\0')
      {
        std::cout << s;
      }
    }

    std::cout << "\n";
  }

  void topThree(const Letter* line, int index)
  {
    int top1 = 0, top2 = 0, top3 = 0;
    char c1 = 0, c2 = 0, c3 = 0;

    for (int i = 0; i < index; ++i)
    {
      if (line[i].count > top1)
      {
        top3 = top2;
        top2 = top1;
        top1 = line[i].count;
        c3 = c2;
        c2 = c1;
        c1 = line[i].name;
      }
      else if (line[i].count > top2)
      {
        top3 = top2;
        top2 = line[i].count;
        c3 = c2;
        c2 = line[i].name;
      }
      else if (line[i].count > top3)
      {
        top3 = line[i].count;
        c3 = line[i].name;
      }
    }

    std::cout << c1 << c2 << c3 << "\n";
  }
}

int main()
{
  const size_t max_size = 1000;
  ershov::Letter input_buffer[max_size];
  size_t index = 0;
  char ch = 0;

  while (std::cin.get(ch) && ch != '\n')
  {
    if (index < max_size - 1 && std::isalpha(ch))
    {
      if (ch >= 'A' && ch <= 'Z')
      {
        ch = ch + ('a' - 'A');
      }

      for (size_t i = 0; i < index; ++i)
      {
        if (input_buffer[i].name == ch)
        {
          input_buffer[i].count += 1;
          break;
        }
      }

      if (input_buffer[index].count == 0)
      {
        input_buffer[index].name = ch;
        input_buffer[index].count += 1;
        index++;
      }
    }
  }

  if (index >= max_size - 1 && std::cin.get(ch) && ch != '\n')
  {
    std::cerr << "Invalid input: length limit\n";
    return 1;
  }

  if (index < 3)
  {
    std::cerr << "Invalid input: incorrent input\n";
    return 1;
  }

  ershov::findMissing(input_buffer);
  ershov::topThree(input_buffer, index);

  return 0;
}
