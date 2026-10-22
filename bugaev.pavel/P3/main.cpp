#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

namespace bugaev {
  const int args_code = 1;
  const int input_code = 2;
  const std::string stack_mode = "1";
  const std::string heap_mode = "2";
  const std::size_t max_size = 10000;

  bool readMatrix(std::ifstream &in, int *matrix, const std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i) {
      if (!(in >> matrix[i])) {
        return false;
      }
    }
    return true;
  }

  int findMinSum(const int *matrix, const int rows, const int cols)
  {
    if ((rows == 0) || (cols == 0)) {
      return 0;
    }
    int min_sum = matrix[cols - 1];
    for (int shift = 1 - rows; shift < cols; ++shift) {
      int sum = 0;
      for (int i = 0; i < rows; ++i) {
        const int j = i + shift;
        if ((j >= 0) && (j < cols)) {
          sum += matrix[i * cols + j];
        }
      }
      if (sum < min_sum) {
        min_sum = sum;
      }
    }
    return min_sum;
  }
}

int main(int argc, char **argv)
{
  if (argc != 4) {
    std::cerr << "Usage: ./lab num input output\n";
    return bugaev::args_code;
  }
  const std::string mode = argv[1];
  if ((mode != bugaev::stack_mode) && (mode != bugaev::heap_mode)) {
    std::cerr << "Error: num must be 1 or 2\n";
    return bugaev::args_code;
  }

  std::ifstream input(argv[2]);
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || (rows < 0) || (cols < 0)) {
    std::cerr << "Error: cannot read matrix size\n";
    return bugaev::input_code;
  }
  const std::size_t size = static_cast< std::size_t >(rows * cols);

  int result = 0;
  bool is_read = false;
  if (mode == bugaev::stack_mode) {
    if (size > bugaev::max_size) {
      std::cerr << "Error: matrix is too large\n";
      return bugaev::input_code;
    }
    int matrix[bugaev::max_size] = {};
    is_read = bugaev::readMatrix(input, matrix, size);
    if (is_read) {
      result = bugaev::findMinSum(matrix, rows, cols);
    }
  } else {
    int *matrix = new int[size];
    is_read = bugaev::readMatrix(input, matrix, size);
    if (is_read) {
      result = bugaev::findMinSum(matrix, rows, cols);
    }
    delete[] matrix;
  }

  if (!is_read) {
    std::cerr << "Error: cannot read matrix\n";
    return bugaev::input_code;
  }
  std::ofstream output(argv[3]);
  output << result << '\n';
  return 0;
}
