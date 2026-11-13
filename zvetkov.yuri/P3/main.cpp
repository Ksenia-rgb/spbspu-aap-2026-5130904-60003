#include <iostream>
#include <fstream>
#include <new>

namespace zvetkov
{
  void printMatrix(int* matrix, int rows, int cols)
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        std::cout << matrix[i * cols + j] << " ";
      }

      std::cout << "\n";
    }
  }

  int minSumMdg(const int* matrix, int rows, int cols)
  {
    int min_sum = 0;
    for (int a = 0; a < rows + cols - 1; a++)
    {
      int sum = 0;

      for (int i = 0; i < rows; i++)
      {
        const int j = a - i;

        if ((j >= 0) && (j < cols))
        {
          sum += matrix[i * cols + j];
        }
      }

      if (a > 0)
      {
        if (sum < min_sum)
        {
          min_sum = sum;
        }
      }
      else
      {
        min_sum = sum;
      }
    }

    return min_sum;
  }

  int const MAX_E = 10000;
}



int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Must be 4 arguments\n";
    return 1;
  }

  const char num = argv[1][0];
  if ((num != '1') && (num != '2'))
  {
    std::cerr << "Wrong num parameter\n";
    return 1;
  }

  std::ifstream file(argv[2]);

  if (!file.is_open())
  {
    std::cerr << "Not opened\n";
    return 2;
  }

  int rows = 0, cols = 0;
  file >> rows >> cols;

  if (!file)
  {
    std::cerr << "INVALID\n";
    return 2;
  }

  if ((1LL * rows * cols > zvetkov::MAX_E) && (num == '1'))
  {
    std::cerr << "Too much elements\n";
    return 2;
  }

  if ((rows < 0) || (cols < 0))
  {
    std::cerr << "INVALID\n";
    return 2;
  }

  if (rows * cols == 0)
  {
    std::ofstream output_file(argv[3]);
    output_file << 0;
    return 0;
  }

  int result = 0;
  if (num == '1')
  {
    int matrix[zvetkov::MAX_E];
    for (int i = 0; i < rows * cols; i++)
    {
      if (!(file >> matrix[i]))
      {
        std::cerr << "Not a number\n";
        return 2;
      }
    }

    result = zvetkov::minSumMdg(matrix, rows, cols);
    zvetkov::printMatrix(matrix, rows, cols);
  }
  else
  {
    int* matrix = nullptr;
    try
    {
      matrix = new int[rows * cols];
    }
    catch (const std::bad_alloc& e)
    {
      std::cerr << "No memory?\n";
      return 2;
    }

    for (int i = 0; i < rows * cols; i++)
    {
      if (!(file >> matrix[i]))
      {
        std::cerr << "Not a number\n";
        delete[] matrix;
        return 2;
      }
    }

    result = zvetkov::minSumMdg(matrix, rows, cols);
    zvetkov::printMatrix(matrix, rows, cols);
    delete[] matrix;
  }

  std::ofstream output_file(argv[3]);
  output_file << result;

  return 0;
}
