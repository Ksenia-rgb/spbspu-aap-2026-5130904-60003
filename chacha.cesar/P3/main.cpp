#include <fstream>
#include <iostream>
#include <limits>
#include <string>

namespace chacha {
int count_saddle(const int *a, int rows, int cols) {
  int count = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int value = a[i * cols + j];

      bool min_in_row = true;
      for (int k = 0; k < cols; ++k) {
        if (a[i * cols + k] < value) {
          min_in_row = false;
        }
      }

      bool max_in_col = true;
      for (int k = 0; k < rows; ++k) {
        if (a[k * cols + j] > value) {
          max_in_col = false;
        }
      }

      if (min_in_row && max_in_col) {
        ++count;
      }
    }
  }
  return count;
}

bool read_matrix(std::ifstream &in, int *a, int size) {
  for (int i = 0; i < size; ++i) {
    if (!(in >> a[i])) {
      return false;
    }
  }
  return true;
}

void run(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Error: se esperan 3 argumentos\n";
    std::exit(1);
  }

  std::string num = argv[1];
  if (num != "1" && num != "2") {
    std::cerr << "Error: el primer parametro debe ser 1 o 2\n";
    std::exit(1);
  }

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Error: no se puede abrir el archivo de entrada\n";
    std::exit(2);
  }

  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error: dimensiones invalidas\n";
    std::exit(2);
  }

  if (rows != 0 && cols > std::numeric_limits<int>::max() / rows) {
    std::cerr << "Error: matriz demasiado grande\n";
    std::exit(2);
  }
  int size = rows * cols;

  int result = 0;

  if (num == "1") {
    if (size > 10000) {
      std::cerr << "Error: matriz demasiado grande\n";
      std::exit(2);
    }
    int fixed[10000];
    if (!read_matrix(in, fixed, size)) {
      std::cerr << "Error: matriz invalida\n";
      std::exit(2);
    }
    result = count_saddle(fixed, rows, cols);
  } else {
    int *dynamic = new int[size + 1];
    if (!read_matrix(in, dynamic, size)) {
      std::cerr << "Error: matriz invalida\n";
      delete[] dynamic;
      std::exit(2);
    }
    result = count_saddle(dynamic, rows, cols);
    delete[] dynamic;
  }

  std::ofstream out(argv[3]);
  if (!out) {
    std::cerr << "Error: no se puede abrir el archivo de salida\n";
    std::exit(2);
  }
  out << result << '\n';
}
}
int main(int argc, char *argv[]) {
  chacha::run(argc, argv);
  return 0;
}
