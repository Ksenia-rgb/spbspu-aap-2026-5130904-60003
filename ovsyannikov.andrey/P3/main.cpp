#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

namespace ovsyannikov {
  const int invalid_arguments = 1;
  const int invalid_data = 2;
  const std::size_t max_fixed_size = 10000;

  bool fillMatrix(std::istream & in, int * matrix, std::size_t count);
  std::size_t countRowsWithoutSeries(const int * matrix, std::size_t rows, std::size_t cols);
}

bool ovsyannikov::fillMatrix(std::istream & in, int * matrix, std::size_t count)
{
  for (std::size_t i = 0; i < count; ++i) {
    in >> matrix[i];
  }
  return static_cast< bool >(in);
}

std::size_t ovsyannikov::countRowsWithoutSeries(const int * matrix, std::size_t rows, std::size_t cols)
{
  std::size_t result = 0;
  for (std::size_t i = 0; i < rows; ++i) {
    bool has_series = false;
    for (std::size_t j = 1; j < cols; ++j) {
      if (matrix[i * cols + j] == matrix[i * cols + j - 1]) {
        has_series = true;
      }
    }
    if (!has_series) {
      ++result;
    }
  }
  return result;
}

int main(int argc, char ** argv)
{
  const int args_count = 4;
  const int input_index = 2;
  const int output_index = 3;

  if (argc != args_count) {
    std::cerr << "usage: <num> <input> <output>\n";
    return ovsyannikov::invalid_arguments;
  }

  const bool is_fixed = (std::strcmp(argv[1], "1") == 0);
  const bool is_dynamic = (std::strcmp(argv[1], "2") == 0);
  if (!is_fixed && !is_dynamic) {
    std::cerr << "first parameter must be 1 or 2\n";
    return ovsyannikov::invalid_arguments;
  }

  std::ifstream input(argv[input_index]);
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || (rows < 0) || (cols < 0)) {
    std::cerr << "invalid matrix size\n";
    return ovsyannikov::invalid_data;
  }
  const std::size_t count = static_cast< std::size_t >(rows) * cols;
  if (is_fixed && (count > ovsyannikov::max_fixed_size)) {
    std::cerr << "matrix is too large\n";
    return ovsyannikov::invalid_data;
  }

  int stack[ovsyannikov::max_fixed_size] = {};
  int * heap = nullptr;
  int * matrix = stack;
  if (is_dynamic) {
    heap = new int[count];
    matrix = heap;
  }

  if (!ovsyannikov::fillMatrix(input, matrix, count)) {
    delete[] heap;
    std::cerr << "invalid matrix elements\n";
    return ovsyannikov::invalid_data;
  }
  const std::size_t result = ovsyannikov::countRowsWithoutSeries(matrix, rows, cols);
  delete[] heap;

  std::ofstream output(argv[output_index]);
  output << result << '\n';
}
