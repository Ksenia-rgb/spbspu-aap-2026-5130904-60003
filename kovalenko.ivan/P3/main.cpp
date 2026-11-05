#include <fstream>
#include <iostream>
#include <new>
#include <string>

namespace kovalenko {
const int max_stack_size = 10000;
const int expected_arg_count = 4;
const int code_bad_arguments = 1;
const int code_bad_data = 2;

static void addSpiral(int *data, const int rows, const int cols) {
  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;
  int increment = 1;
  while (top <= bottom && left <= right) {
    for (int col = left; col <= right; ++col) {
      data[bottom * cols + col] += increment;
      ++increment;
    }
    --bottom;
    for (int row = bottom; row >= top; --row) {
      data[row * cols + right] += increment;
      ++increment;
    }
    --right;
    if (top <= bottom) {
      for (int col = right; col >= left; --col) {
        data[top * cols + col] += increment;
        ++increment;
      }
      ++top;
    }
    if (left <= right) {
      for (int row = top; row <= bottom; ++row) {
        data[row * cols + left] += increment;
        ++increment;
      }
      ++left;
    }
  }
}

static bool readMatrix(std::ifstream &input, int *data, const int count) {
  for (int i = 0; i < count; ++i) {
    if (!(input >> data[i])) {
      return false;
    }
  }
  return true;
}

static void writeMatrix(std::ofstream &output, const int *data, const int rows,
                        const int cols) {
  output << rows << ' ' << cols;
  for (int i = 0; i < rows * cols; ++i) {
    output << ' ' << data[i];
  }
  output << '\n';
}

static int processMatrix(int *data, const int rows, const int cols,
                         std::ifstream &input, const std::string &output_name) {
  if (!readMatrix(input, data, rows * cols)) {
    std::cerr << "Input file has no correct matrix\n";
    return code_bad_data;
  }
  addSpiral(data, rows, cols);
  std::ofstream output(output_name);
  if (!output) {
    std::cerr << "Cant open output file\n";
    return code_bad_data;
  }
  writeMatrix(output, data, rows, cols);
  return 0;
}

static int runProgram(const std::string &mode, const std::string &input_name,
                      const std::string &output_name) {
  std::ifstream input(input_name);
  if (!input) {
    std::cerr << "Cant open input file\n";
    return code_bad_data;
  }
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Input file has no correct matrix\n";
    return code_bad_data;
  }
  const int count = rows * cols;
  if (mode == "1") {
    if (count > max_stack_size) {
      std::cerr << "Matrix is too big for a fixed size\n";
      return code_bad_data;
    }
    int stack_data[max_stack_size] = {};
    return processMatrix(stack_data, rows, cols, input, output_name);
  }
  if (mode == "2") {
    int *const heap_data = new int[count];
    const int code = processMatrix(heap_data, rows, cols, input, output_name);
    delete[] heap_data;
    return code;
  }
  std::cerr << "Unknown mode\n";
  return code_bad_arguments;
}
} // namespace kovalenko

int main(int argc, char *argv[]) {
  if (argc != kovalenko::expected_arg_count) {
    std::cerr << "Usage: ./lab num input output\n";
    return kovalenko::code_bad_arguments;
  }
  const std::string mode = argv[1];
  if (mode != "1" && mode != "2") {
    std::cerr << "Mode can be 1 or 2 only!!!\n";
    return kovalenko::code_bad_arguments;
  }
  try {
    return kovalenko::runProgram(mode, argv[2], argv[3]);
  } catch (std::bad_alloc &) {
    std::cerr << "Not enough memory\n";
    return kovalenko::code_bad_data;
  }
}
