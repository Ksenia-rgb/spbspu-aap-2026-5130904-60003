
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace matrix {
  const int MAX_SIZE = 10000;

  struct Arguments {
    std::string mode;
    std::string input_file;
    std::string output_file;
  };

  bool parseArgs(int argc, char *argv[], Arguments &args)
  {
    if (argc != 4) {
      std::cerr << "Error: expected 3 arguments\n";
      return false;
    }

    args.mode = argv[1];
    args.input_file = argv[2];
    args.output_file = argv[3];

    if (args.mode != "1" && args.mode != "2") {
      std::cerr << "Error: invalid matrix mode\n";
      return false;
    }

    return true;
  }

  bool readMatrix(std::istream &input, std::vector< long long > &data, int &matrix_size)
  {
    int rows = 0;
    int cols = 0;

    if (!(input >> rows >> cols)) {
      std::cerr << "Error: invalid matrix dimensions\n";
      return false;
    }

    if (rows < 0 || cols < 0) {
      std::cerr << "Error: negative matrix dimensions\n";
      return false;
    }

    if (rows > MAX_SIZE || cols > MAX_SIZE || static_cast< long long >(rows) * cols > MAX_SIZE) {
      std::cerr << "Error: matrix is too large\n";
      return false;
    }

    matrix_size = std::min(rows, cols);
    data.resize(static_cast< std::size_t >(matrix_size) * matrix_size);

    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
        long long value = 0;

        if (!(input >> value)) {
          std::cerr << "Error: not enough matrix data\n";
          return false;
        }

        if (row < matrix_size && col < matrix_size) {
          data[static_cast< std::size_t >(row) * matrix_size + col] = value;
        }
      }
    }

    return true;
  }

  bool isUpperTriangular(const std::vector< long long > &data, int matrix_size)
  {
    for (int row = 1; row < matrix_size; ++row) {
      for (int col = 0; col < row; ++col) {
        if (data[static_cast< std::size_t >(row) * matrix_size + col] != 0) {
          return false;
        }
      }
    }

    return matrix_size > 0;
  }

  void printResult(std::ostream &output, bool result)
  {
    output << (result ? "true" : "false") << '\n';
  }
}

int main(int argc, char *argv[])
{
  matrix::Arguments args;

  if (!matrix::parseArgs(argc, argv, args)) {
    return 2;
  }

  std::ifstream input_file(args.input_file);
  if (!input_file) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  std::ofstream output_file(args.output_file);
  if (!output_file) {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }

  std::vector< long long > matrix_data;
  int matrix_size = 0;

  if (!matrix::readMatrix(input_file, matrix_data, matrix_size)) {
    return 2;
  }

  const bool upper_triangle = matrix::isUpperTriangular(matrix_data, matrix_size);
  matrix::printResult(output_file, upper_triangle);

  return 0;
}
