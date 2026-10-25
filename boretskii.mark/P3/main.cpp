#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

namespace boretskii {
const int MAX_ELEMENTS = 10000;

long long findMinSum(int** const matrix, size_t rows, size_t cols)
{
  const int size = static_cast< int >((rows < cols) ? rows : cols);
  long long min_sum = 0;
  bool found = false;

  for (int s = 0; s <= 2 * size - 2; ++s)
  {
    if (s == size - 1)
    {
      continue;
    }

    const int first_row = (s - size + 1 > 0) ? (s - size + 1) : 0;
    const int last_row = (s < size - 1) ? s : (size - 1);

    long long current_sum = 0;
    for (int i = first_row; i <= last_row; ++i)
    {
      current_sum += matrix[i][s - i];
    }

    if (!found || current_sum < min_sum)
    {
      min_sum = current_sum;
      found = true;
    }
  }
  return min_sum;
}
} // namespace boretskii

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "ERROR: invalid arguments\n";
    return 1;
  }

  int num = 0;
  try
  {
    num = std::stoi(std::string(argv[1]));
  }
  catch (...)
  {
    std::cerr << "ERROR: first parameter is not a number\n";
    return 1;
  }

  if (num != 1 && num != 2)
  {
    std::cerr << "ERROR: first parameter is out of range\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  std::ofstream out(argv[3]);
  if (!in.is_open() || !out.is_open())
  {
    std::cerr << "ERROR: cannot open files\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || rows < 0 || cols < 0)
  {
    std::cerr << "ERROR: invalid matrix dimensions\n";
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    out << "0\n";
    return 0;
  }

  long long result = 0;

  if (num == 1)
  {
    if (static_cast< long long >(rows) * cols > boretskii::MAX_ELEMENTS)
    {
      std::cerr << "ERROR: matrix too large\n";
      return 2;
    }

    int data[boretskii::MAX_ELEMENTS] = {};
    for (int i = 0; i < rows * cols; ++i)
    {
      if (!(in >> data[i]))
      {
        std::cerr << "ERROR: invalid matrix data\n";
        return 2;
      }
    }

    int* ptrs[boretskii::MAX_ELEMENTS] = {};
    for (int i = 0; i < rows; ++i)
    {
      ptrs[i] = data + i * cols;
    }

    result = boretskii::findMinSum(ptrs, rows, cols);
  }
  else if (num == 2)
  {
    int** const matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
    {
      matrix[i] = new int[cols];
      for (int j = 0; j < cols; ++j)
      {
        if (!(in >> matrix[i][j]))
        {
          std::cerr << "ERROR: invalid matrix data\n";
          for (int k = 0; k <= i; ++k)
          {
            delete[] matrix[k];
          }
          delete[] matrix;
          return 2;
        }
      }
    }

    result = boretskii::findMinSum(matrix, rows, cols);

    for (int i = 0; i < rows; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  out << result << "\n";
  return 0;
}
