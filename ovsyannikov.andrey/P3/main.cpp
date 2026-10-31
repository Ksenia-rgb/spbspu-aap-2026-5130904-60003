#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>

namespace ovsyannikov {
  template< class T >
  T * createArray(std::size_t size)
  {
    return new T[size];
  }

  const int invalid_arguments = 1;
  const int invalid_data = 2;
  const std::size_t max_fixed_size = 10000;

  int ** createMatrix(std::size_t rows, std::size_t cols);
  void deleteMatrix(int ** matrix, std::size_t rows);
  bool fillRow(std::istream & in, int * row, std::size_t cols);
  bool hasSeries(const int * row, std::size_t cols);
}

int ** ovsyannikov::createMatrix(std::size_t rows, std::size_t cols)
{
  int ** const matrix = createArray< int * >(rows);
  std::size_t created = 0;
  try {
    for (; created < rows; ++created) {
      matrix[created] = createArray< int >(cols);
    }
  } catch (...) {
    deleteMatrix(matrix, created);
    throw;
  }
  return matrix;
}

void ovsyannikov::deleteMatrix(int ** matrix, std::size_t rows)
{
  if (matrix == nullptr) {
    return;
  }
  for (std::size_t i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

bool ovsyannikov::fillRow(std::istream & in, int * row, std::size_t cols)
{
  for (std::size_t j = 0; j < cols; ++j) {
    in >> row[j];
  }
  return static_cast< bool >(in);
}

bool ovsyannikov::hasSeries(const int * row, std::size_t cols)
{
  for (std::size_t j = 1; j < cols; ++j) {
    if (row[j] == row[j - 1]) {
      return true;
    }
  }
  return false;
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
  int rows_input = 0;
  int cols_input = 0;
  if (!(input >> rows_input >> cols_input) || (rows_input < 0) || (cols_input < 0)) {
    std::cerr << "invalid matrix size\n";
    return ovsyannikov::invalid_data;
  }
  const std::size_t rows = rows_input;
  const std::size_t cols = cols_input;
  if (is_fixed && (rows * cols > ovsyannikov::max_fixed_size)) {
    std::cerr << "matrix is too large\n";
    return ovsyannikov::invalid_data;
  }

  int stack[ovsyannikov::max_fixed_size] = {};
  int ** heap = nullptr;
  if (is_dynamic) {
    heap = ovsyannikov::createMatrix(rows, cols);
  }

  std::size_t result = 0;
  for (std::size_t i = 0; i < rows; ++i) {
    int * row = stack + i * cols;
    if (is_dynamic) {
      row = heap[i];
    }
    if (!ovsyannikov::fillRow(input, row, cols)) {
      ovsyannikov::deleteMatrix(heap, rows);
      std::cerr << "invalid matrix elements\n";
      return ovsyannikov::invalid_data;
    }
    if (!ovsyannikov::hasSeries(row, cols)) {
      ++result;
    }
  }
  ovsyannikov::deleteMatrix(heap, rows);

  std::ofstream output(argv[output_index]);
  output << result << '\n';
}
