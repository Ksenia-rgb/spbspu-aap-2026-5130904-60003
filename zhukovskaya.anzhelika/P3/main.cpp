#include <iostream>
#include <fstream>
#include <new>

namespace zhukovskaya {
  void freeMatrix(int** m, int rows)
  {
    if (m == nullptr) {
      return;
    }
    for (int i = 0; i < rows; ++i) {
      delete[] m[i];
    }
    delete[] m;
  }

  int** allocateMatrixDyn(int rows, int cols)
  {
    int** m = new int*[rows];
    for (int i = 0; i < rows; ++i) {
      try {
        m[i] = new int[cols];
      } catch (const std::bad_alloc&) {
        freeMatrix(m, i);
        throw;
      }
    }
    return m;
  }

  int cntLocMin(const int* const* m, int rows, int cols)
  {
    if ((rows < 3) || (cols < 3)) {
      return 0;
    }
    int cnt = 0;
    for (int i = 1; i < (rows - 1); ++i) {
      for (int j = 1; j < (cols - 1); ++j) {
        const int cur = m[i][j];
        if ((cur < m[i - 1][j])
            && (cur < m[i + 1][j])
            && (cur < m[i][j - 1])
            && (cur < m[i][j + 1])
            && (cur < m[i - 1][j - 1])
            && (cur < m[i - 1][j + 1])
            && (cur < m[i + 1][j - 1])
            && (cur < m[i + 1][j + 1])) {
          cnt++;
        }
      }
    }
    return cnt;
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Must be 4 arguments\n";
    return 1;
  }

  if (argv[1][1] != '\0') {
    std::cerr << "First parameter must be '1' or '0'\n";
    return 1;
  }

  int num = 0;
  if (argv[1][0] == '1') {
    num = 1;
  } else if (argv[1][0] == '2') {
    num = 2;
  } else {
    std::cerr << "Wrong first parameter\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "Cannot open file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || (rows < 0) || (cols < 0)) {
    std::cerr << "Invalid dimensions\n";
    return 2;
  }

  if (((rows == 0) && (cols != 0)) || ((rows != 0) && (cols == 0))) {
    std::cerr << "Zero dimension\n";
    return 2;
  }

  const int total = rows * cols;
  int ans = 0;

  if (num == 1) {
    const int maxSize = 10000;
    if (total > maxSize) {
      std::cerr << "Too many elements\n";
      return 2;
    }

    int stackStorage[10000] = {0};
    int* rowPtrs[10000] = {nullptr};

    for (int i = 0; i < rows; ++i) {
      rowPtrs[i] = stackStorage + (i * cols);
      for (int j = 0; j < cols; ++j) {
        if (!(input >> rowPtrs[i][j])) {
          std::cerr << "Read error\n";
          return 2;
        }
      }
    }
    ans = zhukovskaya::cntLocMin(rowPtrs, rows, cols);
  } else {
    int** m = nullptr;
    try {
      m = zhukovskaya::allocateMatrixDyn(rows, cols);
    } catch (const std::bad_alloc&) {
      std::cerr << "Memory allocation error\n";
      return 2;
    }

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(input >> m[i][j])) {
          zhukovskaya::freeMatrix(m, rows);
          std::cerr << "Read error\n";
          return 2;
        }
      }
    }
    ans = zhukovskaya::cntLocMin(m, rows, cols);
    zhukovskaya::freeMatrix(m, rows);
  }

  std::ofstream output(argv[3]);
  if (!output.is_open()) {
    std::cerr << "Cannot open output file\n";
    return 2;
  }

  if ((rows == 0) && (cols == 0)) {
    output << "0 0\n";
  } else {
    output << ans << "\n";
  }

  return 0;
}
