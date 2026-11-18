#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <ostream>

namespace annageldiyev {
  const long long maxFixedElements = 10000;

  int parseMode(const char *arg)
  {
    if (arg[0] != '\0' && arg[1] == '\0') {
      if (arg[0] == '1') {
        return 1;
      }
      if (arg[0] == '2') {
        return 2;
      }
    }
    return 0;
  }

  bool readDimensions(std::istream &in, int &rows, int &cols)
  {
    in >> rows >> cols;
    if (!in) {
      return false;
    }
    return rows >= 0 && cols >= 0;
  }

  bool readElements(std::istream &in, int *data, std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i) {
      in >> data[i];
      if (!in) {
        return false;
      }
    }
    return true;
  }

  bool onlySpacesLeft(std::istream &in)
  {
    in >> std::ws;
    return in.peek() == std::istream::traits_type::eof();
  }

  int spanLength(int index, int size)
  {
    int length = 1;
    if (index > 0) {
      ++length;
    }
    if (index + 1 < size) {
      ++length;
    }
    return length;
  }

  int neighbourCount(int rows, int cols, int row, int col)
  {
    return spanLength(row, rows) * spanLength(col, cols) - 1;
  }

  long long aroundSum(const int *data, int rows, int cols, int row, int col)
  {
    long long sum = 0;
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        const int r = row + dr;
        const int c = col + dc;
        const bool inside = r >= 0 && r < rows && c >= 0 && c < cols;
        if (inside && (dr != 0 || dc != 0)) {
          sum += data[static_cast< std::size_t >(r) * cols + c];
        }
      }
    }
    return sum;
  }

  long long averageInTenths(long long sum, int count)
  {
    if (count == 0) {
      return 0;
    }
    const long long scaled = sum * 10;
    const bool negative = scaled < 0;
    const long long magnitude = negative ? -scaled : scaled;
    const long long divisor = 2LL * count;
    const long long result = (2 * magnitude + count) / divisor;
    return negative ? -result : result;
  }

  void writeTenths(std::ostream &out, long long tenths)
  {
    if (tenths < 0) {
      out << '-';
      tenths = -tenths;
    }
    out << tenths / 10;
    if (tenths % 10 != 0) {
      out << '.' << tenths % 10;
    }
  }

  void writeSmoothed(std::ostream &out, const int *data, int rows, int cols)
  {
    out << rows << ' ' << cols;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        const long long sum = aroundSum(data, rows, cols, i, j);
        const int count = neighbourCount(rows, cols, i, j);
        out << ' ';
        writeTenths(out, averageInTenths(sum, count));
      }
    }
    out << '\n';
  }

  bool saveResult(const char *output_name, const int *data, int rows, int cols)
  {
    std::ofstream output(output_name);
    if (!output) {
      std::cerr << "Cannot open output file\n";
      return false;
    }
    writeSmoothed(output, data, rows, cols);
    return static_cast< bool >(output);
  }

  int runFixed(const char *input_name, const char *output_name)
  {
    std::ifstream input(input_name);
    if (!input) {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
    int rows = 0;
    int cols = 0;
    if (!readDimensions(input, rows, cols)) {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    const long long count = static_cast< long long >(rows) * cols;
    if (count > maxFixedElements) {
      std::cerr << "Matrix is too large for a fixed-size array\n";
      return 2;
    }
    int storage[maxFixedElements] = {};
    const std::size_t size = static_cast< std::size_t >(count);
    if (!readElements(input, storage, size) || !onlySpacesLeft(input)) {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    return saveResult(output_name, storage, rows, cols) ? 0 : 2;
  }

  int runDynamic(const char *input_name, const char *output_name)
  {
    std::ifstream input(input_name);
    if (!input) {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
    int rows = 0;
    int cols = 0;
    if (!readDimensions(input, rows, cols)) {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    const std::size_t height = static_cast< std::size_t >(rows);
    const std::size_t width = static_cast< std::size_t >(cols);
    const std::size_t count = height * width;
    const std::unique_ptr< int[] > storage(new (std::nothrow) int[count]);
    if (!storage) {
      std::cerr << "Not enough memory for the matrix\n";
      return 2;
    }
    if (!readElements(input, storage.get(), count) || !onlySpacesLeft(input)) {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    return saveResult(output_name, storage.get(), rows, cols) ? 0 : 2;
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " num input output\n";
    return 1;
  }
  const int mode = annageldiyev::parseMode(argv[1]);
  if (mode == 0) {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }
  if (mode == 1) {
    return annageldiyev::runFixed(argv[2], argv[3]);
  }
  return annageldiyev::runDynamic(argv[2], argv[3]);
}
