#include <cstddef>
#include <fstream>
#include <iostream>

namespace somov {
  const char stack = '1';
  const char heap = '2';
  const int error_input_file = 2;
  const int error_input = 1;
  const int correct_out = 0;
  const int args_count = 4;
  const std::size_t max_stack_size = 1000;

  bool readMatrix(std::istream &input, int *matrix, std::size_t size);
  int maxSideDiagSum(const int *matrix, int rows, int cols);
}

bool somov::readMatrix(std::istream &input, int *matrix, std::size_t size)
{
  for (std::size_t i = 0; i < size; ++i) {
    if (!(input >> matrix[i])) {
      return false;
    }
  }
  return true;
}

int somov::maxSideDiagSum(const int *matrix, const int rows, const int cols)
{
  if ((rows <= 0) || (cols <= 0)) {
    return 0;
  }

  int max_sum = 0;
  bool is_found = false;

  for (int diag = 0; diag < (rows + cols - 1); ++diag) {
    if (diag == (cols - 1)) {
      continue;
    }
    int current_sum = 0;
    for (int row = 0; row < rows; ++row) {
      const int col = diag - row;
      if ((0 <= col) && (col < cols)) {
        current_sum += matrix[row * cols + col];
      }
    }
    if (!is_found || (current_sum > max_sum)) {
      max_sum = current_sum;
      is_found = true;
    }
  }
  return max_sum;
}

int main(int argc, char *argv[])
{
  if (argc < somov::args_count) {
    std::cerr << "Not enough arguments";
    return somov::error_input;
  }

  if (argc > somov::args_count) {
    std::cerr << "Too many arguments";
    return somov::error_input;
  }

  const char mode = *argv[1];
  if ((mode != somov::stack) && (mode != somov::heap)) {
    std::cerr << "First parameter must be 1 or 2 " << mode;
    return somov::error_input;
  }

  std::ifstream in(argv[2]);
  std::ofstream out(argv[3]);
  if (!in) {
    std::cerr << "Cannot open input file: " << argv[2];
    return somov::error_input_file;
  }
  if (!out) {
    std::cerr << "Cannot open output file: " << argv[3];
    return somov::error_input_file;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || (rows < 0) || (cols < 0)) {
    std::cerr << "Can`t read matrix size";
    return somov::error_input_file;
  }
  const std::size_t size = static_cast< std::size_t >(rows) * static_cast< std::size_t >(cols);

  bool is_read = false;
  int result = 0;

  if (mode == somov::stack) {
    if (size > somov::max_stack_size) {
      std::cerr << "Matrix is too big for stack";
      return somov::error_input;
    }
    int matrix[somov::max_stack_size] = {};
    is_read = somov::readMatrix(in, matrix, size);
    if (is_read) {
      result = somov::maxSideDiagSum(matrix, rows, cols);
    }
  } else {
    int *const matrix = new int[size];
    is_read = somov::readMatrix(in, matrix, size);
    if (is_read) {
      result = somov::maxSideDiagSum(matrix, rows, cols);
    }
    delete[] matrix;
  }

  if (!is_read) {
    std::cerr << "Matrix can`t be readen";
    return somov::error_input_file;
  }

  out << result << "\n";
  in.close();
  out.close();

  return somov::correct_out;
}
