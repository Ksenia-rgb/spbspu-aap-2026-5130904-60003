#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

namespace boretskii {
  const std::size_t max_stack_size = 10000;
  const int error_arguments = 1;
  const int error_input = 2;
  const int args_count = 4;

  bool readMatrix(std::istream &input, int *matrix, std::size_t size);
  long long findMinSum(const int *matrix, std::size_t rows, std::size_t cols);
}

bool boretskii::readMatrix(std::istream &input, int *matrix, std::size_t size)
{
  for (std::size_t i = 0; i < size; ++i) {
    if (!(input >> matrix[i])) {
      return false;
    }
  }
  return true;
}

long long boretskii::findMinSum(const int *matrix, std::size_t rows, std::size_t cols)
{
  const int size = static_cast< int >(std::min(rows, cols));
  const int stride = static_cast< int >(cols);

  long long min_sum = 0;
  bool is_found = false;
  for (int diag = 0; diag <= (2 * size - 2); ++diag) {
    if (diag == (size - 1)) {
      continue;
    }

    int first_row = 0;
    if (diag > (size - 1)) {
      first_row = diag - size + 1;
    }
    int last_row = size - 1;
    if (diag < (size - 1)) {
      last_row = diag;
    }

    long long current_sum = 0;
    for (int row = first_row; row <= last_row; ++row) {
      current_sum += matrix[row * stride + (diag - row)];
    }

    if (!is_found || (current_sum < min_sum)) {
      min_sum = current_sum;
      is_found = true;
    }
  }
  return min_sum;
}

int main(int argc, char *argv[])
{
  if (argc != boretskii::args_count) {
    std::cerr << "ERROR: invalid arguments\n";
    return boretskii::error_arguments;
  }

  const std::string mode = argv[1];
  const bool is_stack = (mode == "1");
  const bool is_heap = (mode == "2");
  if (!is_stack && !is_heap) {
    std::cerr << "ERROR: first parameter must be 1 or 2\n";
    return boretskii::error_arguments;
  }

  std::ifstream in(argv[2]);
  std::ofstream out(argv[3]);
  if (!in || !out) {
    std::cerr << "ERROR: cannot open files\n";
    return boretskii::error_input;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || (rows < 0) || (cols < 0)) {
    std::cerr << "ERROR: invalid matrix dimensions\n";
    return boretskii::error_input;
  }
  const std::size_t size = static_cast< std::size_t >(rows) * static_cast< std::size_t >(cols);

  bool is_read = false;
  long long result = 0;

  if (is_stack) {
    if (size > boretskii::max_stack_size) {
      std::cerr << "ERROR: matrix is too big for stack\n";
      return boretskii::error_input;
    }
    int matrix[boretskii::max_stack_size] = {};
    is_read = boretskii::readMatrix(in, matrix, size);
    if (is_read) {
      result = boretskii::findMinSum(matrix, rows, cols);
    }
  } else {
    int *const matrix = new int[size];
    is_read = boretskii::readMatrix(in, matrix, size);
    if (is_read) {
      result = boretskii::findMinSum(matrix, rows, cols);
    }
    delete[] matrix;
  }

  if (!is_read) {
    std::cerr << "ERROR: invalid matrix data\n";
    return boretskii::error_input;
  }

  out << result << "\n";
  return 0;
}
