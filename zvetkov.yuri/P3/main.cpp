#include <iostream>
#include <fstream>

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

int minSumMdg(int* matrix, int rows, int cols)
{
  int min_sum = 0;
  for (int a = 0; a < rows + cols - 1; a++)
  {
    int sum = 0;

    for (int i = 0; i < rows; i++)
    {
      int j = a - i;

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
int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Must be 4 arguments\n";
    return 1;
  }

  char num = argv[1][0];
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

  int rows, cols;
  file >> rows >> cols;

  if (!file)
  {
    std::cerr << "INVALID\n";
    return 2;
  }

  if ((rows * cols > MAX_E) && (num == '1'))
  {
    std::cerr << "Too much elements\n";
    return 2;
  }

  if (rows * cols == 0)
  {
    std::ofstream output_file(argv[3]);
    output_file << 0;
    return 0;
  }

  if (num == '1')
  {
    int matrix[MAX_E];
    for (int i = 0; i < rows * cols; i++)
    {
      if (!(file >> matrix[i]))
      {
        std::cerr << "Not a number\n";
        return 2;
      }
    }

    std::ofstream output_file(argv[3]);
    output_file << minSumMdg(matrix, rows, cols);
    printMatrix(matrix, rows, cols);
  }
  else
  {
    int* matrix = new int[rows * cols];
    for (int i = 0; i < rows * cols; i++)
    {
      if (!(file >> matrix[i]))
      {
        std::cerr << "Not a number\n";
        delete[] matrix;
        return 2;
      }
    }

    std::ofstream output_file(argv[3]);
    output_file << minSumMdg(matrix, rows, cols);
    printMatrix(matrix, rows, cols);
    delete[] matrix;
  }



  return 0;
}
