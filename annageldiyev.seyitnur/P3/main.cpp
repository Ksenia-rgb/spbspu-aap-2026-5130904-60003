#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace annageldiyev {

const int SUCCESS = 0;
const int ERR_ARGS = 1;
const int ERR_FILE = 2;
const int MAX_SIZE = 10000;

void readDimensions(std::ifstream &in, int &rows, int &cols) {
  if (!(in >> rows >> cols)) {
    throw std::runtime_error("Error reading dimensions");
  }
  if (rows < 0 || cols < 0) {
    throw std::runtime_error("Negative dimensions");
  }
}

void readElements(std::ifstream &in, int *data, int total) {
  for (int i = 0; i < total; ++i) {
    if (!(in >> data[i])) {
      throw std::runtime_error("Error reading matrix data");
    }
  }
  in >> std::ws;
  if (!in.eof()) {
    throw std::runtime_error("Extra data found");
  }
}

void processMatrix(const int *src, double *dest, int rows, int cols) {
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      double sum = 0.0;
      int count = 0;

      for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
          if (dr == 0 && dc == 0)
            continue;
          const int nr = r + dr;
          const int nc = c + dc;
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            sum += src[nr * cols + nc];
            count++;
          }
        }
      }
      dest[r * cols + c] = (count > 0) ? (sum / count) : src[r * cols + c];
    }
  }
}

void writeMatrix(std::ofstream &out, const double *data, int rows, int cols) {
  out << rows << " " << cols << "\n";
  out << std::fixed << std::setprecision(1);
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (c > 0)
        out << " ";
      out << data[r * cols + c];
    }
    out << "\n";
  }
}

int run(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Error: Invalid number of arguments\n";
    return ERR_ARGS;
  }

  int mode = 0;
  if (std::strcmp(argv[1], "1") == 0)
    mode = 1;
  else if (std::strcmp(argv[1], "2") == 0)
    mode = 2;
  else {
    std::cerr << "Error: First argument must be 1 or 2\n";
    return ERR_ARGS;
  }

  std::ifstream in(argv[2]);
  if (!in.is_open()) {
    std::cerr << "Error: Cannot open input file\n";
    return ERR_FILE;
  }

  int rows = 0, cols = 0;
  try {
    readDimensions(in, rows, cols);
    const int total = rows * cols;

    if (mode == 1) {
      if (total > MAX_SIZE) {
        std::cerr << "Error: Matrix too large for stack\n";
        return ERR_FILE;
      }
      int src[MAX_SIZE];
      double dest[MAX_SIZE];
      readElements(in, src, total);
      processMatrix(src, dest, rows, cols);

      std::ofstream out(argv[3]);
      if (!out.is_open()) {
        std::cerr << "Error: Cannot open output file\n";
        return ERR_FILE;
      }
      writeMatrix(out, dest, rows, cols);
    } else {
      int *const src = new int[total];
      double *const dest = new double[total];
      try {
        readElements(in, src, total);
        processMatrix(src, dest, rows, cols);

        std::ofstream out(argv[3]);
        if (!out.is_open()) {
          std::cerr << "Error: Cannot open output file\n";
          delete[] src;
          delete[] dest;
          return ERR_FILE;
        }
        writeMatrix(out, dest, rows, cols);
      } catch (...) {
        delete[] src;
        delete[] dest;
        throw;
      }
      delete[] src;
      delete[] dest;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return ERR_FILE;
  }

  return SUCCESS;
}
} // namespace annageldiyev

int main(int argc, char *argv[]) { return annageldiyev::run(argc, argv); }
