
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

const int MAX_SIZE = 1000;

int** allocateMatrix(size_t sizem, size_t sizen) {
  int** matrix = new int*[sizem]{};

  try {
    for (size_t i = 0; i < sizem; i++) {
      matrix[i] = new int[sizen];
    }
  } catch (...) {
    for (size_t i = 0; i < sizem; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
    throw;
  }

  return matrix;
}

int readMatrix(std::ifstream& in, int** matrix, size_t sizem,
               size_t sizen) {
  for (size_t i = 0; i < sizem; i++) {
    for (size_t j = 0; j < sizen; j++) {
      if (!(in >> matrix[i][j])) {
        return 1;
      }
    }
  }

  return 0;
}

void delMatrix(int** matrix, size_t sizem) {
  for (size_t i = 0; i < sizem; i++) {
    delete[] matrix[i];
  }

  delete[] matrix;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Expected 3 arguments\n";
    return 1;
  }

  std::string mode = argv[1];

  if (mode != "1" && mode != "2") {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream inputFile(argv[2]);

  if (!inputFile) {
    std::cerr << "Corrupted file\n";
    return 2;
  }

  std::ofstream outputFile(argv[3]);

  if (!outputFile) {
    std::cerr << "Error creating output file\n";
    return 1;
  }

  int rows, cols;
  int str_num = 0;

  if (!(inputFile >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error reading matrix dimensions\n";
    return 2;
  }

  if (rows == 0 && cols == 0) {
    outputFile << 0 << '\n';
    return 0;
  }

  if (rows == 0 || cols == 0 ||
      rows > MAX_SIZE || cols > MAX_SIZE ||
      rows > MAX_SIZE / cols) {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  if (mode == "1") {
    int matrix[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(inputFile >> matrix[i][j])) {
          std::cerr << "Error reading matrix elements\n";
          return 2;
        }
      }
    }

    int max_num = 0;

    for (int i = 0; i < rows; i++) {
      int cnt_num = 1;
      int row_max = 1;

      for (int j = 0; j < cols - 1; j++) {
        if (matrix[i][j] == matrix[i][j + 1]) {
          cnt_num++;
        } else {
          cnt_num = 1;
        }

        if (cnt_num > row_max) {
          row_max = cnt_num;
        }
      }

      if (row_max > max_num) {
        max_num = row_max;
        str_num = i + 1;
      }
    }
  }

  if (mode == "2") {
    int** matrixd = allocateMatrix(rows, cols);

    if (readMatrix(inputFile, matrixd, rows, cols) != 0) {
      std::cerr << "Error reading matrix elements\n";
      delMatrix(matrixd, rows);
      return 2;
    }

    int max_num = 0;

    for (int i = 0; i < rows; i++) {
      int cnt_num = 1;
      int row_max = 1;

      for (int j = 0; j < cols - 1; j++) {
        if (matrixd[i][j] == matrixd[i][j + 1]) {
          cnt_num++;
        } else {
          cnt_num = 1;
        }

        if (cnt_num > row_max) {
          row_max = cnt_num;
        }
      }

      if (row_max > max_num) {
        max_num = row_max;
        str_num = i + 1;
      }
    }

    delMatrix(matrixd, rows);
  }

  outputFile << str_num << '\n';

  if (!outputFile) {
    std::cerr << "Error writing output file\n";
    return 1;
  }

  return 0;
}
