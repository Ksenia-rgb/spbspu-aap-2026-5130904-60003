#include <fstream>
#include <iostream>
#include <string>

const int MAX_SIZE = 1000;

int **allocateMatrix(int size_m, int size_n)
{
  int **const matrix = new int *[size_m]{};

  try
  {
    for (int i = 0; i < size_m; i++)
    {
      matrix[i] = new int[size_n];
    }
  }
  catch (...)
  {
    for (int i = 0; i < size_m; i++)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
    throw;
  }

  return matrix;
}

int readMatrix(std::ifstream &input_file,
               int **const matrix,
               int size_m, int size_n)
{
  for (int i = 0; i < size_m; i++)
  {
    for (int j = 0; j < size_n; j++)
    {
      if (!(input_file >> matrix[i][j]))
      {
        return 1;
      }
    }
  }

  return 0;
}

void deleteMatrix(int **const matrix, int size_m)
{
  for (int i = 0; i < size_m; i++)
  {
    delete[] matrix[i];
  }

  delete[] matrix;
}

int findLongestRow(int **const matrix, int rows, int cols)
{
  int best_row = 1;
  int max_length = 0;

  for (int i = 0; i < rows; i++)
  {
    int current_length = 1;

    for (int j = 1; j < cols; j++)
    {
      if (matrix[i][j] == matrix[i][j - 1])
      {
        current_length++;
      }
      else
      {
        current_length = 1;
      }

      if (current_length > max_length)
      {
        max_length = current_length;
        best_row = i + 1;
      }
    }

    if (max_length == 0)
    {
      max_length = 1;
      best_row = i + 1;
    }
  }

  return best_row;
}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  const std::string mode = argv[1];

  if (mode != "1" && mode != "2")
  {
    std::cerr << "Invalid mode\n";
    return 1;
  }

  std::ifstream input_file(argv[2]);
  if (!input_file.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 1;
  }

  std::ofstream output_file(argv[3]);
  if (!output_file.is_open())
  {
    std::cerr << "Cannot open output file\n";
    return 1;
  }

  int rows = 0;
  int cols = 0;

  if (!(input_file >> rows >> cols))
  {
    std::cerr << "Invalid matrix dimensions\n";
    return 1;
  }

  if (rows == 0 && cols == 0)
  {
    output_file << 0 << '\n';
    return 0;
  }

  if (rows <= 0 || cols <= 0 || rows > MAX_SIZE || cols > MAX_SIZE)
  {
    std::cerr << "Invalid matrix dimensions\n";
    return 1;
  }

  int best_row = 1;

  if (mode == "1")
  {
    static int matrix[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        if (!(input_file >> matrix[i][j]))
        {
          std::cerr << "Invalid matrix data\n";
          return 1;
        }
      }
    }

    int max_length = 0;

    for (int i = 0; i < rows; i++)
    {
      int current_length = 1;

      for (int j = 1; j < cols; j++)
      {
        if (matrix[i][j] == matrix[i][j - 1])
        {
          current_length++;
        }
        else
        {
          current_length = 1;
        }

        if (current_length > max_length)
        {
          max_length = current_length;
          best_row = i + 1;
        }
      }

      if (max_length == 0)
      {
        max_length = 1;
        best_row = i + 1;
      }
    }
  }
  else
  {
    int **matrix = nullptr;

    try
    {
      matrix = allocateMatrix(rows, cols);
    }
    catch (...)
    {
      std::cerr << "Memory allocation failed\n";
      return 1;
    }

    if (readMatrix(input_file, matrix, rows, cols) != 0)
    {
      deleteMatrix(matrix, rows);
      std::cerr << "Invalid matrix data\n";
      return 1;
    }

    best_row = findLongestRow(matrix, rows, cols);

    deleteMatrix(matrix, rows);
  }

  output_file << best_row << '\n';

  return 0;
}
