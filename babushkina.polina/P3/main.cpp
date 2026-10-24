#include <climits>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

const int MAX_SIZE = 100;

namespace babushkina {
  void deleteMatrix(int **m, int rows)
  {
    if (m == nullptr) {
      return;
    }
    for (int i = 0; i < rows; i++) {
      delete[] m[i];
    }
    delete[] m;
  }

  int **allocateMatrix(int rows, int cols)
  {
    if (rows <= 0 || cols <= 0) {
      throw std::invalid_argument("ERROR: bad size");
    }
    int **const m = new int *[rows]();
    try {
      for (int i = 0; i < rows; i++) {
        m[i] = new int[cols]();
      }
    } catch (...) {
      deleteMatrix(m, rows);
      throw;
    }
    return m;
  }

  bool readMatrix(std::istream &in, int **matrix, int rows, int cols)
  {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(in >> matrix[i][j])) {
          return false;
        }
      }
    }
    char extra = '\0';
    if (in >> extra) {
      return false;
    }
    return true;
  }

  bool readMatrix(std::istream &in, int matrix[][MAX_SIZE], int rows, int cols)
  {
    int *ptrs[MAX_SIZE];
    for (int i = 0; i < rows; i++) {
      ptrs[i] = matrix[i];
    }
    return readMatrix(in, ptrs, rows, cols);
  }

  long long maxSumParallelMinorDiag(int **matrix, int rows, int cols)
  {
    long long max_sum = LLONG_MIN;
    long long cur_sum = 0;
    int j = 0;
    for (int k = 0; k <= rows + cols - 2; k++) {
      if (k == cols - 1) {
        continue;
      }
      for (int i = 0; i < rows && i <= k; i++) {
        j = k - i;
        if (j < cols) {
          cur_sum += matrix[i][j];
        }
      }
      if (max_sum < cur_sum) {
        max_sum = cur_sum;
      }
      cur_sum = 0;
    }
    return max_sum;
  }

  long long maxSumParallelMinorDiag(int matrix[][MAX_SIZE], int rows, int cols)
  {
    int *ptrs[MAX_SIZE];
    for (int i = 0; i < rows; i++) {
      ptrs[i] = matrix[i];
    }
    return maxSumParallelMinorDiag(ptrs, rows, cols);
  }
}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <num> <input> <output>\n";
    return 1;
  }
  int num = 0;
  try {
    num = std::stoi(argv[1]);
  } catch (...) {
    std::cerr << "ERROR: first argument is not a number\n";
    return 1;
  }
  if (num != 1 && num != 2) {
    std::cerr << "ERROR: first parameter is out of range\n";
    return 1;
  }

  const char *const input_name = argv[2];
  const char *const output_name = argv[3];

  std::ifstream input(input_name);

  if (!input) {
    std::cerr << "ERROR: cannot open " << input_name << "\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  long long max_sum = 0;

  if (!(input >> rows >> cols)) {
    std::cerr << "ERROR: file is not a matrix or empty\n";
    return 2;
  }
  if (rows < 0 || cols < 0) {
    std::cerr << "ERROR: bad size\n";
    return 2;
  }
  char extra = '\0';
  if (rows == 0 || cols == 0) {
    if (input >> extra) {
      std::cerr << "ERROR: extra data after empty matrix\n";
      return 2;
    }
    std::ofstream output(output_name);
    if (!output) {
      std::cerr << "ERROR: cannot open " << output_name << "\n";
      return 2;
    }
    output << rows << " " << cols << "\n0\n";
    return 0;
  }

  if (num == 1) {
    if (rows > MAX_SIZE || cols > MAX_SIZE) {
      std::cerr << "ERROR: size is out of range\n";
      return 2;
    }

    int matrix[MAX_SIZE][MAX_SIZE]{};

    if (!(babushkina::readMatrix(input, matrix, rows, cols))) {
      std::cerr << "ERROR: file is not a matrix\n";
      return 2;
    }

    max_sum = babushkina::maxSumParallelMinorDiag(matrix, rows, cols);
  } else if (num == 2) {
    int **matrix = nullptr;
    try {
      matrix = babushkina::allocateMatrix(rows, cols);
    } catch (...) {
      std::cerr << "ERROR: memory allocation failed\n";
      return 2;
    }
    if (!(babushkina::readMatrix(input, matrix, rows, cols))) {
      std::cerr << "ERROR: file is not a matrix\n";
      babushkina::deleteMatrix(matrix, rows);
      return 2;
    }
    max_sum = babushkina::maxSumParallelMinorDiag(matrix, rows, cols);
    babushkina::deleteMatrix(matrix, rows);
  }
  std::ofstream output(output_name);
  if (!output) {
    std::cerr << "ERROR: cannot open " << output_name << "\n";
    return 2;
  }
  output << rows << " " << cols << "\n" << max_sum << "\n";
  return 0;
}
