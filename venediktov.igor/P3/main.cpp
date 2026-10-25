#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

void allocateMatrix(int *&matrix, size_t rows, size_t cols) {
  matrix = new int[rows * cols]{};
}

bool isTriangleBottom(const int *matrix, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = i + 1; j < cols; j++) {
      if (matrix[i * cols + j] != 0) {
        return false;
      }
    }
  }
  return true;
}

bool isNumber(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

bool canReadFile(std::ifstream &file_input, size_t &rows, size_t &cols) {
  if (!file_input.is_open()) {
    return false;
  }

  if (!(file_input >> rows >> cols)) {
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }

  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  if (!isNumber(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }

  int mode = std::atoi(argv[1]);

  if (mode != 1 && mode != 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t rows = 0;
  size_t cols = 0;

  std::ifstream file_input(argv[2]);
  std::ofstream file_output(argv[3]);

  if (!canReadFile(file_input, rows, cols)) {
    std::cerr << "Error: File is empty or invalid dimensions\n";
    return 2;
  }

  if (rows == 0 || cols == 0) {
    file_output << "true\n";
    file_input.close();
    file_output.close();
    return 0;
  }

  bool result = true;

  if (mode == 1) {
    const size_t MAX_SIZE = 10000;
    int matrix[MAX_SIZE];

    if (rows * cols > MAX_SIZE) {
      std::cerr
          << "Error: Matrix size exceeds stack capacity (10000 elements)\n";
      return 2;
    }

    bool read_success = true;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (!(file_input >> matrix[i * cols + j])) {
          read_success = false;
          break;
        }
      }
      if (!read_success) {
        break;
      }
    }

    if (!read_success) {
      std::cerr << "Error: Invalid matrix data\n";
      return 2;
    }

    result = isTriangleBottom(matrix, rows, cols);
  } else if (mode == 2) {
    int *matrix = nullptr;

    allocateMatrix(matrix, rows, cols);

    bool read_success = true;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (!(file_input >> matrix[i * cols + j])) {
          read_success = false;
          break;
        }
      }
      if (!read_success) {
        break;
      }
    }

    if (!read_success) {
      delete[] matrix;
      matrix = nullptr;
      std::cerr << "Error: Invalid matrix data\n";
      return 2;
    }

    result = isTriangleBottom(matrix, rows, cols);

    delete[] matrix;
    matrix = nullptr;
  }

  if (result) {
    file_output << "true\n";
  } else {
    file_output << "false\n";
  }

  file_input.close();
  file_output.close();
  return 0;
}