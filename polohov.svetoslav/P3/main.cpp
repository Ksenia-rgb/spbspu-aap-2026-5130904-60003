
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

const int MAX_SIZE = 1000;

int** allocate_matrix(std::size_t size_m, std::size_t size_n) {
  int** const matrix = new int*[size_m]{};

  try {
    for (std::size_t i = 0; i < size_m; i++) {
      matrix[i] = new int[size_n];
    }
  } catch (...) {
    for (std::size_t i = 0; i < size_m; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
    throw;
  }

  return matrix;
}

int read_matrix(std::ifstream& input_file, int** const matrix,
                std::size_t size_m, std::size_t size_n) {
  for (std::size_t i = 0; i < size_m; i++) {
    for (std::size_t j = 0; j < size_n; j++) {
      if (!(input_file >> matrix[i][j])) {
        return 1;
      }
    }
  }

  return 0;
}

void delete_matrix(int** const matrix, std::size_t size_m) {
  for (std::size_t i = 0; i < size_m; i++) {
    delete[] matrix[i];
  }

  delete[] matrix;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Expected 3 arguments\n";
    return 1;
  }

  const std::string mode = argv[1];

  if (mode != "1" && mode != "2") {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream input_file(argv[2]);

  if (!input_file) {
    std::cerr << "Corrupted file\n";
    return 2;
  }

  std::ofstream output_file(argv[3]);

  if (!output_file) {
    std::cerr << "Error creating output file\n";
    return 1;
  }

  int rows = 0;
  int cols = 0;
  int str_num = 0;

  if (!(input_file >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error reading matrix dimensions\n";
    return 2;
  }

  if (rows == 0 && cols == 0) {
    output_file << 0 << '\n';
    return output_file ? 0 : 1;
  }

  if (rows == 0 || cols == 0 ||
      rows > MAX_SIZE || cols > MAX_SIZE ||
      rows > MAX_SIZE / cols) {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  if (mode == "1") {
    static int matrix[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(input_file >> matrix[i][j])) {
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
    int** const matrix_d = allocate_matrix(rows, cols);

    if (read_matrix(input_file, matrix_d, rows, cols) != 0) {
      std::cerr << "Error reading matrix elements\n";
      delete_matrix(matrix_d, rows);
      return 2;
    }

    int max_num = 0;

    for (int i = 0; i < rows; i++) {
      int cnt_num = 1;
      int row_max = 1;

      for (int j = 0; j < cols - 1; j++) {
        if (matrix_d[i][j] == matrix_d[i][j + 1]) {
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

    delete_matrix(matrix_d, rows);
  }

  output_file << str_num << '\n';

  if (!output_file) {
    std::cerr << "Error writing output file\n";
    return 1;
  }

  return 0;
}
