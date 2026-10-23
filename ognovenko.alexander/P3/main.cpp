#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

namespace ognovenko
{
  int numColLsr(const int* matrix, int rows, int cols)
  {
    if (matrix == nullptr || rows <= 0 || cols <= 0) {
      return 0;
    }

    const std::size_t column_count = static_cast<std::size_t>(cols);
    int best_column = 0;
    int best_length = 0;

    for (int column = 0; column < cols; ++column) {
      int current_length = 1;
      int max_length = 1;
      const std::size_t column_position = static_cast<std::size_t>(column);

      for (int row = 1; row < rows; ++row) {
        const std::size_t previous_index = static_cast<std::size_t>(row - 1) * column_count + column_position;
        const std::size_t current_index = static_cast<std::size_t>(row) * column_count + column_position;

        if (matrix[previous_index] == matrix[current_index]) {
          ++current_length;
          if (current_length > max_length) {
            max_length = current_length;
          }
        } else {
          current_length = 1;
        }
      }

      if (max_length > best_length) {
        best_length = max_length;
        best_column = column + 1;
      }
    }

    return best_column;
  }

  bool parseTaskNumber(const char* text, int& task_number)
  {
    if (text == nullptr) {
      return false;
    }

    try {
      std::size_t position = 0;
      const int value = std::stoi(text, &position);
      if (text[position] != '\0') {
        return false;
      }
      if (value != 1 && value != 2) {
        return false;
      }
      task_number = value;
      return true;
    } catch (const std::invalid_argument&) {
      return false;
    } catch (const std::out_of_range&) {
      return false;
    }
  }

  bool readMatrix(std::ifstream& input, int* matrix, int rows, int cols)
  {
    const std::size_t count = static_cast<std::size_t>(rows) * static_cast<std::size_t>(cols);

    if (matrix == nullptr && count > 0) {
      return false;
    }

    for (std::size_t index = 0; index < count; ++index) {
      if (!(input >> matrix[index])) {
        return false;
      }
    }

    input >> std::ws;
    return input.eof();
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " num input output\n";
    return 1;
  }

  int task_number = 0;
  if (!ognovenko::parseTaskNumber(argv[1], task_number)) {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "Cannot read matrix dimensions\n";
    return 2;
  }

  if (rows < 0 || cols < 0) {
    std::cerr << "Matrix dimensions must be >= 0\n";
    return 2;
  }

  const std::size_t row_count = static_cast<std::size_t>(rows);
  const std::size_t column_count = static_cast<std::size_t>(cols);

  if (rows != 0 && column_count > std::numeric_limits<std::size_t>::max() / row_count) {
    std::cerr << "Matrix is too large\n";
    return 2;
  }

  const std::size_t element_count = row_count * column_count;
  if (task_number == 1 && element_count > 10000) {
    std::cerr << "Matrix is too large\n";
    return 2;
  }

  int result = 0;

  if (task_number == 1) {
    int matrix[10000] = {};

    if (!ognovenko::readMatrix(input, matrix, rows, cols)) {
      std::cerr << "Cannot read matrix\n";
      return 2;
    }

    result = ognovenko::numColLsr(matrix, rows, cols);
  } else {
    int* matrix = nullptr;

    if (element_count > 0) {
      try {
        matrix = new int[element_count];
      } catch (const std::bad_alloc&) {
        std::cerr << "Cannot allocate matrix\n";
        return 2;
      }
    }

    if (!ognovenko::readMatrix(input, matrix, rows, cols)) {
      delete[] matrix;
      std::cerr << "Cannot read matrix\n";
      return 2;
    }

    result = ognovenko::numColLsr(matrix, rows, cols);
    delete[] matrix;
  }

  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Cannot open output file\n";
    return 2;
  }

  output << result << '\n';
  if (!output) {
    std::cerr << "Cannot write result\n";
    return 2;
  }

  return 0;
}