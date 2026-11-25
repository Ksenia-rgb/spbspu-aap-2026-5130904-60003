#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace erarslan {

  int const kMaxFixedElements = 10000;

  bool parseTaskNumber(char const* text, int& task)
  {
    char* end = nullptr;
    long const value = std::strtol(text, &end, 10);
    if (end == text || *end != '\0') {
      return false;
    }
    if (value != 1 && value != 2) {
      return false;
    }
    task = static_cast< int >(value);
    return true;
  }

  bool readMatrix(std::istream& stream, int* elements, long long count)
  {
    for (long long i = 0; i < count; ++i) {
      if (!(stream >> elements[i])) {
        return false;
      }
    }
    return true;
  }

  bool hasExtraData(std::istream& stream)
  {
    char extra = '\0';
    return static_cast< bool >(stream >> extra);
  }

  int countLocalMinima(int const* matrix, int rows, int cols)
  {
    int count = 0;
    for (int i = 1; i + 1 < rows; ++i) {
      for (int j = 1; j + 1 < cols; ++j) {
        int const value = matrix[i * cols + j];
        bool is_local_minimum = true;
        for (int di = -1; di <= 1 && is_local_minimum; ++di) {
          for (int dj = -1; dj <= 1 && is_local_minimum; ++dj) {
            if (di == 0 && dj == 0) {
              continue;
            }
            if (value >= matrix[(i + di) * cols + (j + dj)]) {
              is_local_minimum = false;
            }
          }
        }
        if (is_local_minimum) {
          ++count;
        }
      }
    }
    return count;
  }

  int processAndWrite(char const* output_path, std::istream& input, int* matrix, int rows, int cols)
  {
    long long const elementCount = static_cast< long long >(rows) * static_cast< long long >(cols);
    if (!readMatrix(input, matrix, elementCount) || hasExtraData(input)) {
      std::cerr << "Error: file content cannot be interpreted as a two-dimensional array\n";
      return 2;
    }

    std::ofstream output(output_path);
    if (!output) {
      std::cerr << "Error: cannot open output file \"" << output_path << "\"\n";
      return 2;
    }

    if (elementCount == 0) {
      output << rows << ' ' << cols << '\n';
    } else {
      output << countLocalMinima(matrix, rows, cols) << '\n';
    }

    return output ? 0 : 2;
  }

  int run(int argc, char* argv[])
  {
    if (argc != 4) {
      std::cerr << "Error: expected 3 arguments: lab num input output\n";
      return 1;
    }

    int task = 0;
    if (!parseTaskNumber(argv[1], task)) {
      std::cerr << "Error: first parameter must be 1 or 2\n";
      return 1;
    }

    std::ifstream input(argv[2]);
    if (!input) {
      std::cerr << "Error: cannot open input file \"" << argv[2] << "\"\n";
      return 2;
    }

    int rows = 0;
    int cols = 0;
    if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
      std::cerr << "Error: file content cannot be interpreted as a two-dimensional array\n";
      return 2;
    }

    if (task == 1) {
      if (static_cast< long long >(rows) * cols > kMaxFixedElements) {
        std::cerr << "Error: matrix is too large for a fixed-size array\n";
        return 2;
      }
      int storage[kMaxFixedElements];
      return processAndWrite(argv[3], input, storage, rows, cols);
    }

    long long const elementCount = static_cast< long long >(rows) * static_cast< long long >(cols);
    int* matrix = nullptr;
    try {
      matrix = new int[static_cast< std::size_t >(elementCount)];
    } catch (...) {
      std::cerr << "Error: cannot allocate memory for the matrix\n";
      return 2;
    }

    int const result = processAndWrite(argv[3], input, matrix, rows, cols);
    delete[] matrix;
    return result;
  }

}

int main(int argc, char* argv[])
{
  return erarslan::run(argc, argv);
}
