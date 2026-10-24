#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace vakulov {
  const int success = 0;
  const int invalidArguments = 1;
  const int processingError = 2;
}

const int maxSize = 10000;

int readAndCheckArg(int argc, char *argv[])
{
  if (argc > 4) {
    throw std::invalid_argument("Too many arguments");
  } else if (argc < 4) {
    throw std::invalid_argument("Not enough arguments");
  }

  const std::string argument = argv[1];
  if (argument == "1") {
    return 1;
  } else if (argument == "2") {
    return 2;
  }

  throw std::invalid_argument("First parameter must be 1 or 2");
}

void readRowsAndCols(std::ifstream &input, int &rows, int &cols)
{
  if (!(input >> rows >> cols)) {
    throw std::runtime_error("Size read error");
  }
  if (rows < 0 || cols < 0) {
    throw std::runtime_error("Matrix dimensions cannot be negative");
  }
}

void readMatrix(std::ifstream &input, int *matrix, std::size_t size)
{
  for (std::size_t i = 0; i < size; i++) {
    if (!(input >> matrix[i])) {
      throw std::runtime_error("Invalid matrix data");
    }
  }

  input >> std::ws;
  if (input.bad() || !input.eof()) {
    throw std::runtime_error("Unexpected data after the matrix");
  }
}

double calculateAverage(const int *matrix, int rows, int cols, int row, int col)
{
  double sum = 0.0;
  int count = 0;
  int firstRow = row;
  int lastRow = row;
  int firstCol = col;
  int lastCol = col;

  if (row > 0) {
    firstRow = row - 1;
  }
  if (row + 1 < rows) {
    lastRow = row + 1;
  }
  if (col > 0) {
    firstCol = col - 1;
  }
  if (col + 1 < cols) {
    lastCol = col + 1;
  }

  for (int i = firstRow; i <= lastRow; i++) {
    for (int j = firstCol; j <= lastCol; j++) {
      if (i != row || j != col) {
        sum += matrix[std::size_t(i) * cols + j];
        count++;
      }
    }
  }

  if (count == 0) {
    return matrix[std::size_t(row) * cols + col];
  }

  return sum / count;
}

void smoothMatrix(const int *source, double *result, int rows, int cols)
{
  if (rows == 0 || cols == 0) {
    return;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result[std::size_t(i) * cols + j] = calculateAverage(source, rows, cols, i, j);
    }
  }
}

void writeMatrix(const char *outputName, const double *matrix, int rows, int cols)
{
  std::ofstream output(outputName);
  if (!output) {
    throw std::runtime_error("Cannot open the output file");
  }

  const int precision = 1;
  output << rows << " " << cols << "\n";
  output << std::fixed << std::setprecision(precision);

  if (rows != 0 && cols != 0) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (j > 0) {
          output << " ";
        }
        output << matrix[std::size_t(i) * cols + j];
      }
      output << "\n";
    }
  }

  output.close();
  if (!output) {
    throw std::runtime_error("Cannot write the output file");
  }
}

void processMatrix(std::ifstream &input, const char *outputName, int *source, double *result, int rows, int cols)
{
  const std::size_t size = std::size_t(rows) * cols;
  readMatrix(input, source, size);
  smoothMatrix(source, result, rows, cols);
  writeMatrix(outputName, result, rows, cols);
}

void processStack(std::ifstream &input, const char *outputName, int rows, int cols)
{
  const std::size_t size = std::size_t(rows) * cols;
  if (size > maxSize) {
    throw std::runtime_error("Matrix exceeds stack capacity");
  }

  int source[maxSize] = {};
  double result[maxSize] = {};
  processMatrix(input, outputName, source, result, rows, cols);
}

void processHeap(std::ifstream &input, const char *outputName, int rows, int cols)
{
  const std::size_t size = std::size_t(rows) * cols;
  int *source = nullptr;
  double *result = nullptr;

  try {
    source = new int[size]();
    result = new double[size]();
    processMatrix(input, outputName, source, result, rows, cols);
  } catch (...) {
    delete[] source;
    delete[] result;
    throw;
  }

  delete[] source;
  delete[] result;
}

int main(int argc, char *argv[])
{
  int var = 0;
  try {
    var = readAndCheckArg(argc, argv);
  } catch (const std::invalid_argument &e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    return vakulov::invalidArguments;
  }

  try {
    std::ifstream input(argv[2]);
    if (!input) {
      throw std::runtime_error("Cannot open the input file");
    }

    int rows = 0, cols = 0;
    readRowsAndCols(input, rows, cols);

    const std::size_t size = std::size_t(rows) * cols;
    if (rows != 0 && size / rows != std::size_t(cols)) {
      throw std::runtime_error("Matrix dimensions are too large");
    }

    if (var == 1) {
      processStack(input, argv[3], rows, cols);
    } else {
      processHeap(input, argv[3], rows, cols);
    }
  } catch (const std::exception &e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    return vakulov::processingError;
  }

  return vakulov::success;
}
