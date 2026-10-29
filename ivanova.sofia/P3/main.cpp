#include <exception>
#include <fstream>
#include <iostream>
#include <string>

void freeMatrix(int **ptr, int rows)
{
  if ( ptr == nullptr)
  {
    return;
  }

  for (int i = 0; i < rows; i++)
  {
    delete[] ptr[i];
  }
  delete[] ptr;
}

int main(int argvc, char *argv[])
{
  if (argvc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (argvc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  int mode = 0;
  try
  {
    mode = std::stoi(argv[1]);
  }
  catch (...)
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }

  if (mode > 2 || mode < 1)
  {
    std::cerr << "First parametr is out of range\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  std::ofstream out(argv[3]);
  if (!in.is_open())
  {
    std::cerr << "File cannot be open\n";
    return 2;
  }

  int rows = 0;
  int colls = 0;
  if (!(in >> rows >> colls))
  {
    std::cerr << "Invalid file format\n";
    return 2;
  }
  if (rows <= 0 || colls <= 0)
  {
    out << rows << " " << colls << "\n";
    return 0;
  }

  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = colls - 1;
  int count = 1;

  if (mode == 1)
  {
    const int MAX_SIZE = 100;

    if (rows > MAX_SIZE || colls > MAX_SIZE)
    {
      std::cerr << "Matrix size is too big\n";
      return 2;
    }

    int matrix[MAX_SIZE][MAX_SIZE]{};
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < colls; j++)
      {
        if (!(in >> matrix[i][j]))
        {
          std::cerr << "Error reading matrix element\n";
          return 2;
        }
      }
    }

    while (top <= bottom && left <= right)
    {
      for (int i = bottom; i >= top; i--)
      {
        matrix[i][left] -= count;
        count++;
      }
      left++;

      if (left <= right)
      {
        for (int j = left; j <= right; j++)
        {
          matrix[top][j] -= count;
          count++;
        }
        top++;
      }

      if (top <= bottom)
      {
        for (int i = top; i <= bottom; i++)
        {
          matrix[i][right] -= count;
          count++;
        }
        right--;
      }

      if (left <= right && top <= bottom)
      {
        for (int j = right; j >= left; j--)
        {
          matrix[bottom][j] -= count;
          count++;
        }
        bottom--;
      }
    }

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < colls; j++)
      {
        out << matrix[i][j] << " ";
      }
      out << "\n";
    }
  }

  if (mode == 2)
  {
    int initialized_rows = 0;
    try
    {
      int **ptr = new int*[rows]{};

      for (int i = 0; i < rows; i++)
      {
        ptr[i] = new int[colls];
        initialized_rows++;

        for (int j = 0; j < colls; j++)
        {
          if (!(in >> ptr[i][j]))
          {
            std::cerr << "Error reading matrix element\n";

            freeMatrix(ptr, initialized_rows);
            return 2;
          }
        }
      }

      while (top <= bottom && left <= right)
      {
        for (int i = bottom; i >= top; i--)
        {
          ptr[i][left] -= count;
          count++;
        }
        left++;

        if (left <= right)
        {
          for (int j = left; j <= right; j++)
          {
            ptr[top][j] -= count;
            count++;
          }
          top++;
        }

        if (top <= bottom)
        {
          for (int i = top; i <= bottom; i++)
          {
            ptr[i][right] -= count;
            count++;
          }
          right--;
        }

        if (left <= right && top <= bottom)
        {
          for (int j = right; j >= left; j--)
          {
            ptr[bottom][j] -= count;
            count++;
          }
          bottom--;
        }
      }

      for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < colls; j++)
        {
          out << ptr[i][j] << " ";
        }
        out << "\n";
      }

      freeMatrix(ptr, rows);
    }

    catch (const std::bad_alloc &e)
    {
      std::cerr << "Error: out of memory (bad_alloc)\n";
      return 3;
    }
  }
  out.close();
  return 0;
}
