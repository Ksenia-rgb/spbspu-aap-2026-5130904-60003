#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace binkovsky
{
int run(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Error: expected num, input and output\n";
        return 1;
    }

    if (argv[1][0] < '1' || argv[1][0] > '2' ||
        argv[1][1] != '\0')
    {
        std::cerr << "Error: num must be 1 or 2\n";
        return 1;
    }

    int mode = argv[1][0] - '0';

    std::ifstream input(argv[2]);
    if (!input)
    {
        std::cerr << "Error: cannot open input file\n";
        return 2;
    }

    int rows = 0;
    int cols = 0;

    if (!(input >> rows >> cols) || rows < 0 || cols < 0 ||
        ((rows == 0) != (cols == 0)))
    {
        std::cerr << "Error: invalid matrix dimensions\n";
        return 2;
    }

    std::ofstream output(argv[3]);
    if (!output)
    {
        std::cerr << "Error: cannot open output file\n";
        return 2;
    }

    if (rows == 0 && cols == 0)
    {
        output << 0 << '\n';
        return 0;
    }

    if (rows > std::numeric_limits<int>::max() / cols)
    {
        std::cerr << "Error: matrix is too large\n";
        return 2;
    }

    const int count = rows * cols;

    if (mode == 1 && count > 10000)
    {
        std::cerr << "Error: matrix exceeds 10000 elements\n";
        return 2;
    }

    int fixed_matrix[10000];
    int* matrix = fixed_matrix;

    if (mode == 2)
    {
        matrix = new (std::nothrow) int[count];
        if (matrix == nullptr)
        {
            std::cerr << "Error: cannot allocate matrix\n";
            return 2;
        }
    }

    for (int i = 0; i < count; ++i)
    {
        if (!(input >> matrix[i]))
        {
            std::cerr << "Error: invalid matrix data\n";

            if (mode == 2)
            {
                delete[] matrix;
            }

            return 2;
        }
    }

    long long maximum_sum = 0;
    bool has_sum = false;

    for (int start_row = 1; start_row < rows; ++start_row)
    {
        long long sum = 0;
        int row = start_row;
        int col = 0;

        while (row < rows && col < cols)
        {
            sum += matrix[row * cols + col];
            ++row;
            ++col;
        }

        if (!has_sum || sum > maximum_sum)
        {
            maximum_sum = sum;
            has_sum = true;
        }
    }

    output << maximum_sum << '\n';

    if (mode == 2)
    {
        delete[] matrix;
    }

    return 0;
}
}

int main(int argc, char* argv[])
{
    return binkovsky::run(argc, argv);
}
