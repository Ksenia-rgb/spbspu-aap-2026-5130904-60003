#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>

namespace matrix {
  const std::size_t MAX_SIZE = 10000;

  struct Arguments {
    int mode;
    const char * input_file;
    const char * output_file;
  };

  bool parseArgs(int argc, char * argv[], Arguments & args)
  {
    if (argc != 4) {
      std::cerr << "Error: expected 3 arguments\n";
      return false;
    }

    if (argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2')) {
      std::cerr << "Error: invalid matrix mode\n";
      return false;
    }

    args.mode = argv[1][0] - '0';
    args.input_file = argv[2];
    args.output_file = argv[3];

    return true;
  }

  bool readDimensions(std::istream & input, std::size_t & rows, std::size_t & cols)
  {
    long long row_count = 0;
    long long col_count = 0;

    if (!(input >> row_count >> col_count) || row_count < 0 || col_count < 0) {
      std::cerr << "Error: invalid matrix dimensions\n";
      return false;
    }

    rows = static_cast< std::size_t >(row_count);
    cols = static_cast< std::size_t >(col_count);

    return true;
  }

  bool fitsLimit(std::size_t rows, std::size_t cols)
  {
    const std::size_t size = std::min(rows, cols);

    return size == 0 || size <= MAX_SIZE / size;
  }

  bool readMatrix(std::istream & input, int * data, std::size_t rows, std::size_t cols)
  {
    const std::size_t size = std::min(rows, cols);

    for (std::size_t row = 0; row < rows; ++row) {
      for (std::size_t col = 0; col < cols; ++col) {
        int value = 0;

        if (!(input >> value)) {
          std::cerr << "Error: not enough matrix data\n";
          return false;
        }

        if (row < size && col < size) {
          data[row * size + col] = value;
        }
      }
    }

    int extra = 0;

    if (input >> extra) {
      std::cerr << "Error: unexpected data after matrix\n";
      return false;
    }

    return true;
  }

  bool isUpperTriangular(const int * data, std::size_t size)
  {
    if (size == 0) {
      return false;
    }

    for (std::size_t row = 1; row < size; ++row) {
      for (std::size_t col = 0; col < row; ++col) {
        if (data[row * size + col] != 0) {
          return false;
        }
      }
    }

    return true;
  }

  bool printResult(std::ostream & output, bool result)
  {
    output << (result ? "true" : "false") << '\n';
    return static_cast< bool >(output);
  }

  bool processFixed(std::istream & input, std::ostream & output, std::size_t rows, std::size_t cols)
  {
    int data[MAX_SIZE] = {};

    if (!readMatrix(input, data, rows, cols)) {
      return false;
    }

    const std::size_t size = std::min(rows, cols);
    const bool result = isUpperTriangular(data, size);

    return printResult(output, result);
  }

  bool processDynamic(std::istream & input, std::ostream & output, std::size_t rows, std::size_t cols)
  {
    const std::size_t size = std::min(rows, cols);
    const std::size_t count = size * size;

    int * const data = new (std::nothrow) int[count];

    if (data == nullptr && count != 0) {
      std::cerr << "Error: cannot allocate memory\n";
      return false;
    }

    const bool read_ok = readMatrix(input, data, rows, cols);

    if (!read_ok) {
      delete[] data;
      return false;
    }

    const bool result = isUpperTriangular(data, size);
    const bool write_ok = printResult(output, result);

    delete[] data;

    return write_ok;
  }
}

int main(int argc, char * argv[])
{
  matrix::Arguments args;

  if (!matrix::parseArgs(argc, argv, args)) {
    return 2;
  }

  std::ifstream input_file(args.input_file);

  if (!input_file.is_open()) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  std::ofstream output_file(args.output_file);

  if (!output_file.is_open()) {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }

  std::size_t rows = 0;
  std::size_t cols = 0;
  if (!matrix::readDimensions(input_file, rows, cols)) {
    return 2;
  }

  if (args.mode == 1 && !matrix::fitsLimit(rows, cols)) {
    std::cerr << "Error: matrix exceeds fixed array capacity\n";
    return 2;
  }

  bool success = false;

  if (args.mode == 1) {
    success = matrix::processFixed(input_file, output_file, rows, cols);
  } else {
    success = matrix::processDynamic(input_file, output_file, rows, cols);
  }

  return success ? 0 : 2;
}
