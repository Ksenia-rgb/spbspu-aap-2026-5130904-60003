#include <cstdlib>
#include <fstream>
#include <iostream>

namespace glavan {
  const int max_size = 10000;

  bool readMatrix(std::istream & in, int * matrix, int size)
  {
    for (int i = 0; i < size; ++i) {
      if (!(in >> matrix[i])) {
        return false;
      }
    }
    return true;
  }

  int countDiagonals(const int * matrix, int rows, int cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    int count = 0;
    for (int shift = 1 - rows; shift < cols; ++shift) {
      if (shift == 0) {
        continue;
      }
      bool has_zero = false;
      for (int row = 0; row < rows; ++row) {
        int col = row + shift;
        if (col >= 0 && col < cols && matrix[row * cols + col] == 0) {
          has_zero = true;
        }
      }
      if (!has_zero) {
        ++count;
      }
    }
    return count;
  }

  int processFixed(std::istream & in, std::ostream & out, int rows, int cols)
  {
    int matrix[max_size] = {};
    if (!readMatrix(in, matrix, rows * cols)) {
      std::cerr << "Error: wrong matrix elements\n";
      return 2;
    }
    out << countDiagonals(matrix, rows, cols) << '\n';
    return 0;
  }

  int processDynamic(std::istream & in, std::ostream & out, int rows, int cols)
  {
    int * matrix = new int[rows * cols];
    if (!readMatrix(in, matrix, rows * cols)) {
      std::cerr << "Error: wrong matrix elements\n";
      delete[] matrix;
      return 2;
    }
    out << countDiagonals(matrix, rows, cols) << '\n';
    delete[] matrix;
    return 0;
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4) {
    std::cerr << "Error: wrong number of arguments\n";
    return 1;
  }

  char * end = nullptr;
  long num = std::strtol(argv[1], &end, 10);
  if (end == argv[1] || *end != '\0' || (num != 1 && num != 2)) {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error: wrong matrix size\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (num == 1) {
    return glavan::processFixed(input, output, rows, cols);
  }
  return glavan::processDynamic(input, output, rows, cols);
}
