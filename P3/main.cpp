#include <iostream>
#include <fstream>
#include <string>
#include <new>

int** allocateMatrix(int rows, int cols)
{
  int** m = new int*[rows]();
  try
  {
    for (int i = 0; i < rows; ++i)
    {
      m[i] = new int[cols]();
    }
  }
  catch (...)
  {
    for (int i = 0; i < rows; ++i)
    {
      delete[] m[i];
    }
    delete[] m;
    throw;
  }
  return m;
}

void freeMatrix(int** m, int rows)
{
  if (m == nullptr)
  {
    return;
  }
  for (int i = 0; i < rows; ++i)
  {
    delete[] m[i];
  }
  delete[] m;
}

bool readToDyn(std::ifstream& in, int** matrix, int rows, int cols)
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (!(in >> matrix[i][j]))
      {
        return false;
      }
    }
  }
  return true;
}

void spiralTransform(int** matrix, int rows, int cols)
{
  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;
  int current_increment = 1;
  int total_elements = rows * cols;

  while (current_increment <= total_elements)
  {
    for (int i = top; i <= bottom && current_increment <= total_elements; ++i)
    {
      matrix[i][left] += current_increment;
      current_increment++;
    }
    left++;

    for (int j = left; j <= right && current_increment <= total_elements; ++j)
    {
      matrix[bottom][j] += current_increment;
      current_increment++;
    }
    bottom--;

    for (int i = bottom; i >= top && current_increment <= total_elements; --i)
    {
      matrix[i][right] += current_increment;
      current_increment++;
    }
    right--;

    for (int j = right; j >= left && current_increment <= total_elements; --j)
    {
      matrix[top][j] += current_increment;
      current_increment++;
    }
    top++;
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Invalid number of arguments" << std::endl;
    return 1;
  }

  std::string num_param = argv[3];
  if (num_param != "1" && num_param != "2")
  {
    std::cerr << "Error: First parameter must be 1 or 2" << std::endl;
    return 1;
  }

  std::ifstream input_file(argv[1]);
  if (!input_file.is_open())
  {
    std::cerr << "Error: Cannot open input file" << std::endl;
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(input_file >> rows >> cols) || rows < 0 || cols < 0)
  {
    std::cerr << "Error: Invalid matrix dimensions" << std::endl;
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    std::ofstream output_file(argv[2]);
    if (output_file.is_open())
    {
      output_file << "0 0" << std::endl;
      return 0;
    }
    return 2;
  }

  int** matrix = nullptr;
  try
  {
    matrix = allocateMatrix(rows, cols);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: cannot allocate matrix" << std::endl;
    return 1;
  }

  if (!readToDyn(input_file, matrix, rows, cols))
  {
    std::cerr << "ERROR: bad matrix element" << std::endl;
    freeMatrix(matrix, rows);
    return 2;
  }
  input_file.close();

  spiralTransform(matrix, rows, cols);

  std::ofstream output_file(argv[2]);
  if (!output_file.is_open())
  {
    std::cerr << "Error: Cannot open output file" << std::endl;
    freeMatrix(matrix, rows);
    return 2;
  }

  output_file << rows << " " << cols;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      output_file << " " << matrix[i][j];
    }
  }
  output_file << std::endl;
  output_file.close();

  freeMatrix(matrix, rows);

  return 0;
}
