#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

namespace boretskii {
const int MAX_ROWS = 100;
const int MAX_COLS = 100;
const int MAX_ELEMENTS = 10000;

long long findMinSum(const int *const *matrix, size_t rows, size_t cols) {
  long long min_sum = -1;
  bool found = false;

  for (int k = -(static_cast<int>(cols) - 1); k <= static_cast<int>(rows) - 1;
       ++k) {
    if (k == 0)
      continue;

    long long current_sum = 0;
    bool has_elements = false;

    for (int i = 0; i < static_cast<int>(rows); ++i) {
      const int j = i - k;
      if (j >= 0 && j < static_cast<int>(cols)) {
        current_sum += matrix[i][j];
        has_elements = true;
      }
    }

    if (has_elements) {
      if (!found) {
        min_sum = current_sum;
        found = true;
      } else if (current_sum < min_sum) {
        min_sum = current_sum;
      }
    }
  }
  return min_sum;
}
} // namespace boretskii

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "ERROR: invalid arguments\n";
    return 1;
  }

  int num = 0;
  try {
    num = std::stoi(std::string(argv[1]));
  } catch (...) {
    std::cerr << "ERROR: first parameter is not a number\n";
    return 1;
  }

  if (num != 1 && num != 2) {
    std::cerr << "ERROR: first parameter is out of range\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  std::ofstream out(argv[3]);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "ERROR: cannot open files\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "ERROR: invalid matrix dimensions\n";
    return 2;
  }

  if (rows == 0 || cols == 0) {
    out << "0\n";
    return 0;
  }

  long long result = 0;

  if (num == 1) {
    if (rows * cols > boretskii::MAX_ELEMENTS) {
      std::cerr << "ERROR: matrix too large\n";
      return 2;
    }

    int matrix[boretskii::MAX_ROWS][boretskii::MAX_COLS] = {};
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(in >> matrix[i][j])) {
          std::cerr << "ERROR: invalid matrix data\n";
          return 2;
        }
      }
    }

    int **const ptrs = new int *[rows];
    for (int i = 0; i < rows; ++i) {
      ptrs[i] = matrix[i];
    }

    result = boretskii::findMinSum(ptrs, rows, cols);
    delete[] ptrs;

  } else if (num == 2) {
    int **const matrix = new int *[rows];
    for (int i = 0; i < rows; ++i) {
      matrix[i] = new int[cols];
      for (int j = 0; j < cols; ++j) {
        if (!(in >> matrix[i][j])) {
          std::cerr << "ERROR: invalid matrix data\n";
          for (int k = 0; k <= i; ++k)
            delete[] matrix[k];
          delete[] matrix;
          return 2;
        }
      }
    }

    result = boretskii::findMinSum(matrix, rows, cols);

    for (int i = 0; i < rows; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  out << result << "\n";
  return 0;
}
