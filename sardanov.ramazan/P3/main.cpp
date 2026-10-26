#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <new>

void freeMatrix(int** matrix, long long rows)
{
  if (matrix == nullptr) {
    return;
  }

  for (long long i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }

  delete[] matrix;
}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Expected 4 arguments\n";
    return 1;
  }

  const std::string arg = argv[1];

  if (arg != "1" && arg != "2") {
    std::cerr << "Error: task number must be 1 or 2\n";
    return 1;
  }

  const int num = std::stoi(arg);

  std::ifstream input(argv[2]);

  if (!input) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  long long rows = 0;
  long long cols = 0;

  if (!(input >> rows >> cols)) {
    std::cerr << "Error: cannot read matrix dimensions\n";
    return 2;
  }

  if (rows < 0 || cols < 0) {
    std::cerr << "Error: matrix dimensions must be non-negative\n";
    return 2;
  }

  const int max_size = 10000;
  int fixed[max_size] = {};
  int* fixed_rows[max_size];

  if (rows != 0 &&
      cols > std::numeric_limits<long long>::max() / rows) {
    std::cerr << "Error: matrix dimensions are too large\n";
    return 2;
  }

  const long long count = rows * cols;

  if (num == 1 && count > max_size) {
    std::cerr << "Error: matrix exceeds fixed array capacity\n";
    return 2;
  }

  if (num == 1 && rows > 0) {
    for (long long i = 0; i < rows; ++i) {
      fixed_rows[i] = fixed + i * cols;
    }
  }

  int** matrix = nullptr;

  if (num == 1) {
    matrix = fixed_rows;
  } else if (rows > 0) {
    try {
      matrix = new int*[rows]{};

      for (long long i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
      }
    } catch (const std::bad_alloc&) {
      std::cerr << "Error: not enough memory for matrix\n";
      freeMatrix(matrix, rows);
      return 2;
    }
  }

  for (long long i = 0; i < rows; ++i) {
    for (long long j = 0; j < cols; ++j) {
      if (!(input >> matrix[i][j])) {
        std::cerr << "Error: missing or invalid matrix element\n";

        if (num == 2) {
          freeMatrix(matrix, rows);
        }

        return 2;
      }
    }
  }

  std::string extra;

  if (input >> extra) {
    std::cerr << "Error: extra data in input file\n";

    if (num == 2) {
      freeMatrix(matrix, rows);
    }

    return 2;
  }

  if (input.bad()) {
    std::cerr << "Error: failed to read input file\n";

    if (num == 2) {
      freeMatrix(matrix, rows);
    }

    return 2;
  }

  std::ofstream output(argv[3]);

  if (!output) {
    std::cerr << "Error: cannot open output file\n";

    if (num == 2) {
      freeMatrix(matrix, rows);
    }

    return 2;
  }

  if (rows == 0 || cols == 0) {
    output << 0 << '\n';

    if (!output) {
      std::cerr << "Error: cannot write output file\n";

      if (num == 2) {
        freeMatrix(matrix, rows);
      }

      return 2;
    }

    if (num == 2) {
      freeMatrix(matrix, rows);
    }

    return 0;
  }

  long long min_sum = std::numeric_limits<long long>::max();
  const long long diagonal_count = rows + cols - 1;

  for (long long d = 0; d < diagonal_count; ++d) {
    long long sum = 0;

    for (long long i = 0; i < rows; ++i) {
      const long long j = d - i;

      if (j >= 0 && j < cols) {
        const int value = matrix[i][j];

        if (value > 0 &&
            sum > std::numeric_limits<long long>::max() - value) {
          std::cerr << "Error: diagonal sum overflow\n";

          if (num == 2) {
            freeMatrix(matrix, rows);
          }

          return 2;
        }

        if (value < 0 &&
            sum < std::numeric_limits<long long>::min() - value) {
          std::cerr << "Error: diagonal sum underflow\n";

          if (num == 2) {
            freeMatrix(matrix, rows);
          }

          return 2;
        }

        sum += value;
      }
    }

    if (sum < min_sum) {
      min_sum = sum;
    }
  }

  output << min_sum << '\n';

  if (!output) {
    std::cerr << "Error: cannot write output file\n";

    if (num == 2) {
      freeMatrix(matrix, rows);
    }

    return 2;
  }

  if (num == 2) {
    freeMatrix(matrix, rows);
  }

  return 0;
}

