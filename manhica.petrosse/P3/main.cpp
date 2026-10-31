
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Error: expected 3 arguments\n";
    return 1;
  }

  const std::string mode = argv[1];

  if (mode != "1" && mode != "2") {
    std::cerr << "Error: invalid matrix mode\n";
    return 1;
  }

  std::ifstream input(argv[2]);

  if (!input.is_open()) {
    std::cerr << "Error: cannot open input file\n";
    return 1;
  }

  std::ofstream output(argv[3]);

  if (!output.is_open()) {
    std::cerr << "Error: cannot open output file\n";
    return 1;
  }

  int rows = 0;
  int cols = 0;

  if (!(input >> rows >> cols)) {
    std::cerr << "Error: invalid matrix dimensions\n";
    return 1;
  }

  if (rows < 0 || cols < 0) {
    std::cerr << "Error: negative matrix dimensions\n";
    return 1;
  }

  if (rows == 0 || cols == 0 || rows != cols) {
    output << "false\n";
    return 0;
  }

  std::vector< std::vector< long long > > matrix(rows, std::vector< long long >(cols));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (!(input >> matrix[i][j])) {
        std::cerr << "Error: not enough matrix data\n";
        return 1;
      }
    }
  }

  bool upper_triangular = true;

  for (int i = 1; i < rows; ++i) {
    for (int j = 0; j < i; ++j) {
      if (matrix[i][j] != 0) {
        upper_triangular = false;
        break;
      }
    }

    if (!upper_triangular) {
      break;
    }
  }

  output << (upper_triangular ? "true" : "false") << '\n';

  return 0;
}

