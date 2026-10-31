#include <iostream>
#include <new>

namespace glavan {
  int processMatrix()
  {
    int rows = 0;
    int cols = 0;

    if (!(std::cin >> rows >> cols) || rows < 0 || cols < 0) {
      std::cerr << "Error: wrong matrix size\n";
      return 1;
    }
    if (rows == 0 || cols == 0) {
      std::cout << 0 << '\n';
      return 0;
    }

    int size = rows * cols;
    int * matrix = new (std::nothrow) int[size];
    if (matrix == nullptr) {
      std::cerr << "Error: not enough memory\n";
      return 2;
    }

    for (int i = 0; i < size; ++i) {
      if (!(std::cin >> matrix[i])) {
        std::cerr << "Error: wrong matrix elements\n";
        delete[] matrix;
        return 1;
      }
    }

    int count = 0;
    for (int shift = 1 - rows; shift < cols; ++shift) {
      if (shift == 0) {
        continue;
      }
      bool has_zero = false;
      for (int row = 0; row < rows; ++row) {
        int col = row + shift;
        if (col >= 0 && col < cols && matrix[row * cols + col] == 0) {
          has_zero = true;
        }
      }
      if (!has_zero) {
        ++count;
      }
    }

    delete[] matrix;
    std::cout << count << '\n';
    return 0;
  }
}

int main()
{
  return glavan::processMatrix();
}
