#include <climits>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>

namespace annageldiyev {
constexpr int SUCCESS = 0;
constexpr int ERR_ARGS = 1;
constexpr int ERR_FILE = 2;
constexpr int MAX_SIZE = 10000;

int parseMode(const char *arg)
{
  if (std::strcmp(arg, "1") == 0) {
    return 1;
  }
  if (std::strcmp(arg, "2") == 0) {
    return 2;
  }
  return 0;
}

bool readElements(std::istream &in, int *data, const int total)
{
  for (int i = 0; i < total; ++i) {
    if (!(in >> data[i])) {
      return false;
    }
  }
  return true;
}

void smoothMatrix(const int *src, double *dest, const int rows, const int cols)
{
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      long long sum = 0;
      int count = 0;
      for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
          const int nr = r + dr;
          const int nc = c + dc;
          const bool isSelf = (dr == 0 && dc == 0);
          if (!isSelf && nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            sum += src[nr * cols + nc];
            ++count;
          }
        }
      }
      dest[r * cols + c] = (count > 0) ? static_cast<double>(sum) / count : 0.0;
    }
  }
}

void writeMatrix(std::ostream &out, const double *data, const int rows, const int cols)
{
  out << std::setprecision(15);
  out << rows << ' ' << cols;
  for (int i = 0; i < rows * cols; ++i) {
    const double rounded = std::round(data[i] * 10.0) / 10.0;
    out << ' ' << (rounded + 0.0);
  }
  out << '\n';
}

int processMatrix(std::istream &in, std::ostream &out, int *src, double *dest, const int rows, const int cols)
{
  if (!readElements(in, src, rows * cols)) {
    std::cerr << "Error: invalid matrix data\n";
    return ERR_FILE;
  }
  smoothMatrix(src, dest, rows, cols);
  writeMatrix(out, dest, rows, cols);
  return SUCCESS;
}

int run(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Error: expected 3 arguments: num input output\n";
    return ERR_ARGS;
  }
  const int mode = parseMode(argv[1]);
  if (mode == 0) {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return ERR_ARGS;
  }

  std::ifstream in(argv[2]);
  if (!in.is_open()) {
    std::cerr << "Error: cannot open input file\n";
    return ERR_FILE;
  }
  int rows = 0;
  int cols = 0;
  if (!(in >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error: invalid matrix size\n";
    return ERR_FILE;
  }
  if (static_cast<long long>(rows) * cols > INT_MAX) {
    std::cerr << "Error: matrix is too large\n";
    return ERR_FILE;
  }
  const int total = rows * cols;

  std::ofstream out(argv[3]);
  if (!out.is_open()) {
    std::cerr << "Error: cannot open output file\n";
    return ERR_FILE;
  }

  int result = SUCCESS;
  if (mode == 1) {
    if (total > MAX_SIZE) {
      std::cerr << "Error: matrix is too large\n";
      return ERR_FILE;
    }
    int src[MAX_SIZE];
    double dest[MAX_SIZE];
    result = processMatrix(in, out, src, dest, rows, cols);
  } else {
    int *const src = new (std::nothrow) int[total];
    double *const dest = new (std::nothrow) double[total];
    if (src == nullptr || dest == nullptr) {
      std::cerr << "Error: not enough memory\n";
      result = ERR_FILE;
    } else {
      result = processMatrix(in, out, src, dest, rows, cols);
    }
    delete[] src;
    delete[] dest;
  }
  return result;
}
} // namespace annageldiyev

int main(int argc, char *argv[])
{
  return annageldiyev::run(argc, argv);
}
