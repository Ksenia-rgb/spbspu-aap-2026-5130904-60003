#include <iostream>
#include <fstream>
#include <string>
#include <new>

int** allocateMatrix(int rows, int cols)
{
  int** const m = new int*[rows]();
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

bool readMatr(std::ifstream& in, int** matrix, int rows, int cols)
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
  if (!in.is_open() || !out.is_open())
  {
    std::cerr << "File cannot be open\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols))
  {
    std::cerr << "Invalid file format\n";
    return 2;
  }
  if (rows <= 0 || cols <= 0)
  {
    out << rows << " " << cols << "\n";
    return 0;
  }

  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;
  int count = 1;

  if (mode == 1)
  {
    const int MAX_SIZE = 100;

    if (rows > MAX_SIZE || cols > MAX_SIZE)
    {
      std::cerr << "Matrix size is too big\n";
      return 2;
    }

    int matrix[MAX_SIZE][MAX_SIZE]{};
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
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
      for (int j = 0; j < cols; j++)
      {
        out << matrix[i][j] << " ";
      }
      out << "\n";
    }
  }

  else if (mode == 2)
  {
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

    if (!readMatr(in, matrix, rows, cols))
    {
      std::cerr << "ERROR: bad matrix element" << std::endl;
      freeMatrix(matrix, rows);
      return 2;
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
      for (int j = 0; j < cols; j++)
      {
        out << matrix[i][j] << " ";
      }
      out << "\n";
    }
    freeMatrix(matrix, rows);
  }
  out.close();
  return 0;
}
