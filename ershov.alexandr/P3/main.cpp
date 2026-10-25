#include <iostream>
#include <fstream>
#include <string>

int saddle_Numbers(int *massive, int rows, int cols)
{
  if (rows == 0 || cols == 0)
  {
    return 0;
  }

  int count = 0;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      bool isMax = true;

      int current = massive[i * cols + j];

      for (int c = 0; c < cols; c++)
      {
        if (current > massive[i * cols + c])
        {
          isMax = false;
          break;
        }
      }

      if (!isMax)
      {
        continue;
      }

      for (int r = 0; r < rows; r++)
      {
        if (current < massive[r * cols + j])
        {
          isMax = false;
          break;
        }
      }

      if (isMax)
      {
        count++;
      }
    }
  }

  return count;
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Invalid number of arguments." << std::endl;
    return 1;
  }

  std::string numArg = argv[1];
  std::string inputFileName = argv[2];
  std::string outputFileName = argv[3];

  if (numArg != "1" && numArg != "2")
  {
    std::cerr << "Error: First parameter out of range or not a number." << std::endl;
    return 1;
  }

  int num = numArg[0] - '0';

  std::ifstream inFile(inputFileName);

  if (!inFile.is_open())
  {
    std::cerr << "Error: Cannot open input file." << std::endl;
    return 2;
  }

  int rows = 0;
  int cols = 0;

  if (!(inFile >> rows >> cols))
  {
    std::cerr << "Error: Invalid matrix dimensions or file is empty." << std::endl;
    inFile.close();
    return 2;
  }

  if (rows < 0 || cols < 0)
  {
    std::cerr << "Error: Dimensions cannot be negative." << std::endl;
    inFile.close();
    return 2;
  }

  int totalElements = rows * cols;

  int* massiveMatrix = nullptr;
  int stackMatrix[10000];

  if (num == 1)
  {
    if (totalElements > 10000)
    {
      std::cerr << "Error: Matrix exceeds stack limit of 10000 elements." << std::endl;
      inFile.close();
      return 2;
    }

    massiveMatrix = stackMatrix;
  }
  else
  {
    if (totalElements > 0)
    {
      massiveMatrix = new int[totalElements];
    }
  }

  for (int i = 0; i < totalElements; ++i)
  {
    if (!(inFile >> massiveMatrix[i]))
    {
      std::cerr << "Error: Invalid matrix elements or unexpected end of file." << std::endl;
      inFile.close();
      if (num == 2)
      {
        delete[] massiveMatrix;
      }
      return 2;
    }
  }

  int extraElement = 0;

  if (inFile >> extraElement)
  {
    std::cerr << "Error: Too many elements in the file." << std::endl;
    inFile.close();
    if (num == 2)
    {
      delete[] massiveMatrix;
    }
    return 2;
  }

  inFile.close();

  int result = saddle_Numbers(massiveMatrix, rows, cols);

  std::ofstream outFile(outputFileName);

  if (!outFile.is_open())
  {
    std::cerr << "Error: Cannot open output file." << std::endl;
    if (num == 2)
    {
      delete[] massiveMatrix;
    }
    return 2;
  }

  outFile << result << std::endl;
  outFile.close();

  if (num == 2)
  {
    delete[] massiveMatrix;
  }

  return 0;
}
