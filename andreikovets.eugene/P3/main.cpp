#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

const int maxSize = 100;

int readAndCheckArg(int argc, char *argv[])
{
  if (argc > 4) {
    throw std::invalid_argument("Too many argument");
  } else if (argc < 4) {
    throw std::invalid_argument("Not enough arguments");
  }
  int var = 0;
  try {
    var = std::stoi(argv[1]);
  } catch (...) {
    throw std::invalid_argument("First parameter is not a number");
  }
  if (var > 2 || var < 1) {
    throw std::out_of_range("First parameter is out of range");
  }
  return var;
}

void readRowsAndCols(std::ifstream &input, int &rows, int &cols)
{
  if (!(input >> rows >> cols)) {
    throw std::runtime_error("Size read error");
  }
  if (rows > maxSize || cols > maxSize) {
    throw std::runtime_error("ERROR: cols or rows exceed maxSize");
  }
}

int **allocateMatrix(int rows, int cols)
{
  int **const m = new int *[rows]();
  try {
    for (int i = 0; i < rows; i++) {
      m[i] = new int[cols]();
    }
  } catch (...) {
    for (int i = 0; i < rows; i++) {
      delete[] m[i];
    }
    delete[] m;
    throw;
  }
  return m;
}

void freeMatrix(int **matrix, int rows)
{
  if (matrix == nullptr) {
    return;
  }
  for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void readMatrix(std::ifstream &input, int **matrix, int rows, int cols)
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (!(input >> matrix[i][j])) {
        throw std::runtime_error("Invalid matrix data");
      }
    }
  }
}

void readMatrix(std::ifstream &input, int matrix[][maxSize], int rows, int cols)
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (!(input >> matrix[i][j])) {
        throw std::runtime_error("Invalid matrix data");
      }
    }
  }
}

int findMaxSeqRowNum(const int *const *matrix, int rows, int cols)
{
  int cur_len = 1, max_len = 0, row_num = 0;
  for (int i = 0; i < rows; i++) {
    cur_len = 1;
    for (int j = 0; j < cols; j++) {
      if (j > 0) {
        if (matrix[i][j] == matrix[i][j - 1]) {
          cur_len++;
        } else {
          if (cur_len > max_len) {
            max_len = cur_len;
            row_num = i + 1;
          }
          cur_len = 1;
        }
      }
    }
    if (cur_len > max_len) {
      max_len = cur_len;
      row_num = i + 1;
    }
  }
  return row_num;
}

int findMaxSeqRowNum(const int matrix[][maxSize], int rows, int cols)
{
  int cur_len = 1, max_len = 0, row_num = 0;
  for (int i = 0; i < rows; i++) {
    cur_len = 1;
    for (int j = 0; j < cols; j++) {
      if (j > 0) {
        if (matrix[i][j] == matrix[i][j - 1]) {
          cur_len++;
        } else {
          if (cur_len > max_len) {
            max_len = cur_len;
            row_num = i + 1;
          }
          cur_len = 1;
        }
      }
    }
    if (cur_len > max_len) {
      max_len = cur_len;
      row_num = i + 1;
    }
  }
  return row_num;
}

int main(int argc, char *argv[])
{
  try {
    int rows = 0, cols = 0;
    int res = 0;
    const int var = readAndCheckArg(argc, argv);

    std::ifstream input(argv[2]);
    if (!input) {
      std::cerr << "Cannot open: " << argv[2] << "\n";
      return 1;
    }
    readRowsAndCols(input, rows, cols);

    if (var == 1) {
      int matrix[maxSize][maxSize];
      readMatrix(input, matrix, rows, cols);
      res = findMaxSeqRowNum(matrix, rows, cols);
    } else {
      int **matrix = nullptr;
      matrix = allocateMatrix(rows, cols);
      try {
        readMatrix(input, matrix, rows, cols);
        res = findMaxSeqRowNum(matrix, rows, cols);
      } catch (...) {
        freeMatrix(matrix, rows);
        throw;
      }
      freeMatrix(matrix, rows);
    }

    std::ofstream output(argv[3]);
    if (!output) {
      std::cerr << "Cannot open: " << argv[3] << "\n";
      return 1;
    }
    output << res << "\n";
    input.close();
    output.close();
  } catch (const std::invalid_argument &e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  } catch (const std::out_of_range &e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  } catch (const std::runtime_error &e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 2;
  }
  return 0;
}
