#include <iostream>
#include <fstream>
#include <string>

int saddleNumbers(const int * massive, int rows, int cols)
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
      bool is_max = true;

      const int current = massive[i * cols + j];

      for (int c = 0; c < cols; c++)
      {
        if (current > massive[i * cols + c])
        {
          is_max = false;
          break;
        }
      }

      if (!is_max)
      {
        continue;
      }

      for (int r = 0; r < rows; r++)
      {
        if (current < massive[r * cols + j])
        {
          is_max = false;
          break;
        }
      }

      if (is_max)
      {
        count++;
      }
    }
  }

  return count;
}

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Invalid number of arguments." << std::endl;
    return 1;
  }

  const std::string num_arg = argv[1];
  const std::string input_file_name = argv[2];
  const std::string output_file_name = argv[3];

  if (num_arg != "1" && num_arg != "2")
  {
    std::cerr << "Error: First parameter out of range or not a number." << std::endl;
    return 1;
  }

  const int num = num_arg[0] - '0';

  std::ifstream in_file(input_file_name);

  if (!in_file.is_open())
  {
    std::cerr << "Error: Cannot open input file." << std::endl;
    return 2;
  }

  int rows = 0;
  int cols = 0;

  if (!(in_file >> rows >> cols))
  {
    std::cerr << "Error: Invalid matrix dimensions or file is empty." << std::endl;
    in_file.close();
    return 2;
  }

  if (rows < 0 || cols < 0)
  {
    std::cerr << "Error: Dimensions cannot be negative." << std::endl;
    in_file.close();
    return 2;
  }

  const int total_elements = rows * cols;

  int * massive_matrix = nullptr;
  int stack_matrix[10000];

  if (num == 1)
  {
    if (total_elements > 10000)
    {
      std::cerr << "Error: Matrix exceeds stack limit of 10000 elements." << std::endl;
      in_file.close();
      return 2;
    }

    massive_matrix = stack_matrix;
  }
  else
  {
    if (total_elements > 0)
    {
      massive_matrix = new int[total_elements];
    }
  }

  for (int i = 0; i < total_elements; ++i)
  {
    if (!(in_file >> massive_matrix[i]))
    {
      std::cerr << "Error: Invalid matrix elements or unexpected end of file." << std::endl;
      in_file.close();
      if (num == 2)
      {
        delete[] massive_matrix;
      }
      return 2;
    }
  }

  int extra_element = 0;

  if (in_file >> extra_element)
  {
    std::cerr << "Error: Too many elements in the file." << std::endl;
    in_file.close();
    if (num == 2)
    {
      delete[] massive_matrix;
    }
    return 2;
  }

  in_file.close();

  const int result = saddleNumbers(massive_matrix, rows, cols);

  std::ofstream out_file(output_file_name);

  if (!out_file.is_open())
  {
    std::cerr << "Error: Cannot open output file." << std::endl;
    if (num == 2)
    {
      delete[] massive_matrix;
    }
    return 2;
  }

  out_file << result << std::endl;
  out_file.close();

  if (num == 2)
  {
    delete[] massive_matrix;
  }

  return 0;
}
