#include <iostream>
#include <fstream>
#include <string.h>

namespace lagunov
{
  const int MAX_SIZE = 100;

  void freeMatrix(int** matrix, int rows)
  {
    if (matrix == nullptr)
    {
      return;
    }
    for (int i = 0; i < rows; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  int** allocateMatrix(int rows, int cols)
  {
    int** const matrix = new int*[rows];

    try
    {
      for (int i = 0; i < rows; ++i)
      {
        matrix[i] = new int[cols]{};
      }
    }
    catch (...)
    {
      freeMatrix(matrix, rows);
      throw;
    }

    return matrix;
  }

  void incrementMatrix(int** mat, int rows, int cols)
  {
    int min_dim = 0;
    if (rows < cols)
    {
      min_dim = rows;
    }
    else
    {
      min_dim = cols;
    }
    const int layers = min_dim / 2 + min_dim % 2;

    for (int i = 0; i < layers; i++)
    {
      const int increment = i + 1;

      const int top_row = i;
      const int bottom_row = rows - 1 - i;
      const int left_col = i;
      const int right_col = cols - 1 - i;

      if (top_row > bottom_row || left_col > right_col)
      {
        break;
      }

      for (int col = left_col; col <= right_col; col++)
      {
        mat[top_row][col] += increment;
      }

      if (bottom_row != top_row)
      {
        for (int col = left_col; col <= right_col; col++)
        {
          mat[bottom_row][col] += increment;
        }
      }

      for (int row = top_row + 1; row < bottom_row; row++)
      {
        mat[row][left_col] += increment;
      }

      if (right_col != left_col)
      {
        for (int row = top_row + 1; row < bottom_row; row++)
        {
          mat[row][right_col] += increment;
        }
      }
    }
  }

  void incrementMatrix(int mat[][MAX_SIZE], int rows, int cols)
  {
    int min_dim = 0;
    if (rows < cols)
    {
      min_dim = rows;
    }
    else
    {
      min_dim = cols;
    }
    const int layers = min_dim / 2 + min_dim % 2;

    for (int i = 0; i < layers; i++)
    {
      const int increment = i + 1;

      const int top_row = i;
      const int bottom_row = rows - 1 - i;
      const int left_col = i;
      const int right_col = cols - 1 - i;

      if (top_row > bottom_row || left_col > right_col)
      {
        break;
      }

      for (int col = left_col; col <= right_col; col++)
      {
        mat[top_row][col] += increment;
      }

      if (bottom_row != top_row)
      {
        for (int col = left_col; col <= right_col; col++)
        {
          mat[bottom_row][col] += increment;
        }
      }

      for (int row = top_row + 1; row < bottom_row; row++)
      {
        mat[row][left_col] += increment;
      }

      if (right_col != left_col)
      {
        for (int row = top_row + 1; row < bottom_row; row++)
        {
          mat[row][right_col] += increment;
        }
      }
    }
  }

}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " <num> <input> <output>\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "ERROR: cannot open input file\n";
    return 2;
  }

  int rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "ERROR: empty file\n";
    return 2;
  }
  if (rows == 0 && cols == 0)
  {
    std::ofstream output(argv[3]);
    if (!output)
    {
      std::cerr << "ERROR: cannot open file\n";
      return 2;
    }

    output << rows << ' ' << cols;
    return 0;
  }
  if (rows <= 0 || cols <= 0 || rows > lagunov::MAX_SIZE || cols > lagunov::MAX_SIZE)
  {
    std::cerr << "ERROR: invalid matrix size\n";
    return 2;
  }
  if (strcmp(argv[1], "1") == 0)
  {
    int mat[lagunov::MAX_SIZE][lagunov::MAX_SIZE]{};
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        input >> mat[i][j];
      }
    }
    if (!input)
    {
      std::cerr << "ERROR: invalid seqeuence\n";
      return 2;
    }

    lagunov::incrementMatrix(mat, rows, cols);

    std::ofstream output(argv[3]);
    if (!output)
    {
      std::cerr << "ERROR: cannot open output file\n";
      return 1;
    }

    output << rows << ' ' << cols << ' ';
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        output << mat[i][j] << ' ';
      }
    }
  }
  else if (strcmp(argv[1], "2") == 0)
  {
    int** mat = lagunov::allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        input >> mat[i][j];
      }
    }
    if (!input)
    {
      std::cerr << "ERROR: invalid seqeuence\n";
      lagunov::freeMatrix(mat, rows);
      return 2;
    }

    lagunov::incrementMatrix(mat, rows, cols);

    std::ofstream output(argv[3]);
    if (!output)
    {
      std::cerr << "ERROR: cannot open file\n";
      return 1;
    }

    output << rows << ' ' << cols << ' ';
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        output << mat[i][j] << ' ';
      }
    }

    lagunov::freeMatrix(mat, rows);
    mat = nullptr;
  }
  else
  {
    std::cerr << "ERROR: first argument must be 1 or 2\n";
    return 1;
  }
  return 0;
}
