#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <ostream>

namespace annageldiyev
{
  const long long maxFixedElements = 10000;

  // Returns 1 or 2 if the argument is exactly "1" or "2", otherwise 0
  int parseMode(const char * arg)
  {
    if (arg[0] != '\0' && arg[1] == '\0')
    {
      if (arg[0] == '1')
      {
        return 1;
      }
      if (arg[0] == '2')
      {
        return 2;
      }
    }
    return 0;
  }

  bool readDimensions(std::istream & in, int & rows, int & cols)
  {
    in >> rows >> cols;
    if (!in)
    {
      return false;
    }
    return rows >= 0 && cols >= 0;
  }

  bool readElements(std::istream & in, int * data, std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i)
    {
      in >> data[i];
      if (!in)
      {
        return false;
      }
    }
    return true;
  }

  // True if nothing but whitespace remains in the stream
  bool onlySpacesLeft(std::istream & in)
  {
    in >> std::ws;
    return in.peek() == std::istream::traits_type::eof();
  }

  // Sum and number of the (up to 8) neighbours of the element (row, col)
  void collectNeighbours(const int * data, int rows, int cols, int row, int col,
    long long & sum, int & count)
  {
    sum = 0;
    count = 0;
    for (int dr = -1; dr <= 1; ++dr)
    {
      for (int dc = -1; dc <= 1; ++dc)
      {
        if (dr == 0 && dc == 0)
        {
          continue;
        }
        int r = row + dr;
        int c = col + dc;
        if (r < 0 || r >= rows || c < 0 || c >= cols)
        {
          continue;
        }
        sum += data[static_cast< std::size_t >(r) * cols + c];
        ++count;
      }
    }
  }

  // sum / count rounded half away from zero to tenths, in integer arithmetic
  long long averageInTenths(long long sum, int count)
  {
    if (count == 0)
    {
      return 0;
    }
    long long scaled = sum * 10;
    bool negative = scaled < 0;
    long long magnitude = negative ? -scaled : scaled;
    long long result = (2 * magnitude + count) / (2 * static_cast< long long >(count));
    return negative ? -result : result;
  }

  // Prints a number given in tenths: 37 -> 3.7, 50 -> 5, -25 -> -2.5
  void writeTenths(std::ostream & out, long long tenths)
  {
    if (tenths < 0)
    {
      out << '-';
      tenths = -tenths;
    }
    out << tenths / 10;
    if (tenths % 10 != 0)
    {
      out << '.' << tenths % 10;
    }
  }

  void writeSmoothed(std::ostream & out, const int * data, int rows, int cols)
  {
    out << rows << ' ' << cols;
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        long long sum = 0;
        int count = 0;
        collectNeighbours(data, rows, cols, i, j, sum, count);
        out << ' ';
        writeTenths(out, averageInTenths(sum, count));
      }
    }
    out << '\n';
  }

  bool saveResult(const char * outputName, const int * data, int rows, int cols)
  {
    std::ofstream output(outputName);
    if (!output)
    {
      std::cerr << "Cannot open output file\n";
      return false;
    }
    writeSmoothed(output, data, rows, cols);
    return static_cast< bool >(output);
  }

  // Task 1: the matrix is stored in a fixed-size array on the stack
  int runFixed(const char * inputName, const char * outputName)
  {
    std::ifstream input(inputName);
    if (!input)
    {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
    int rows = 0;
    int cols = 0;
    if (!readDimensions(input, rows, cols))
    {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    long long count = static_cast< long long >(rows) * cols;
    if (count > maxFixedElements)
    {
      std::cerr << "Matrix is too large for a fixed-size array\n";
      return 2;
    }
    int storage[maxFixedElements] = {};
    if (!readElements(input, storage, static_cast< std::size_t >(count)) || !onlySpacesLeft(input))
    {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    return saveResult(outputName, storage, rows, cols) ? 0 : 2;
  }

  // Task 2: the matrix is stored in a dynamic array in the free store
  int runDynamic(const char * inputName, const char * outputName)
  {
    std::ifstream input(inputName);
    if (!input)
    {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
    int rows = 0;
    int cols = 0;
    if (!readDimensions(input, rows, cols))
    {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    std::size_t count = static_cast< std::size_t >(rows) * static_cast< std::size_t >(cols);
    std::unique_ptr< int[] > storage(new (std::nothrow) int[count]);
    if (!storage)
    {
      std::cerr << "Not enough memory for the matrix\n";
      return 2;
    }
    if (!readElements(input, storage.get(), count) || !onlySpacesLeft(input))
    {
      std::cerr << "Input is not a two-dimensional array\n";
      return 2;
    }
    return saveResult(outputName, storage.get(), rows, cols) ? 0 : 2;
  }
}

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " num input output\n";
    return 1;
  }
  int mode = annageldiyev::parseMode(argv[1]);
  if (mode == 0)
  {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }
  if (mode == 1)
  {
    return annageldiyev::runFixed(argv[2], argv[3]);
  }
  return annageldiyev::runDynamic(argv[2], argv[3]);
}
