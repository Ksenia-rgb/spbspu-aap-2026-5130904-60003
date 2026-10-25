#include <iostream>
#include <fstream>

namespace boretskii {

    long long findMinSum(int** matrix, int rows, int cols) {
        long long min_sum = -1;
        bool found = false;

        for (int k = 0; k <= rows + cols - 2; ++k) {
            
            if (k == cols - 1) continue;

            long long current_sum = 0;
            bool has_elements = false;

            for (int i = 0; i < rows; ++i) {
                int j = k - i;
                if (j >= 0 && j < cols) {
                    current_sum += matrix[i][j];
                    has_elements = true;
                }
            }

            if (has_elements) {
                if (!found) {
                    min_sum = current_sum;
                    found = true;
                } else if (current_sum < min_sum) {
                    min_sum = current_sum;
                }
            }
        }
        return min_sum;
    }
}

int main(int argc, char* argv[]) {
    using namespace boretskii;

    if (argc != 4) {
        std::cerr << "ERROR: invalid arguments\n";
        return 1;
    }

    int num;
    try {
        num = std::stoi(argv[1]);
    } catch (...) {
        std::cerr << "ERROR: first parameter is not a number\n";
        return 1;
    }

    if (num != 1 && num != 2) {
        std::cerr << "ERROR: first parameter is out of range\n";
        return 1;
    }

    std::ifstream in(argv[2]);
    std::ofstream out(argv[3]);
    if (!in.is_open() || !out.is_open()) {
        std::cerr << "ERROR: cannot open files\n";
        return 2;
    }

    int rows, cols;
    if (!(in >> rows >> cols) || rows <= 0 || cols <= 0) {
        std::cerr << "ERROR: invalid matrix dimensions\n";
        return 2;
    }

    long long result = 0;

    if (num == 1) {
        if (rows * cols > 10000) {
            std::cerr << "ERROR: matrix too large\n";
            return 2;
        }

        int matrix[100][100]; 
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!(in >> matrix[i][j])) {
                    std::cerr << "ERROR: invalid matrix data\n";
                    return 2;
                }
            }
        }

        int** ptrs = new int*[rows];
        for (int i = 0; i < rows; ++i) ptrs[i] = matrix[i];

        result = findMinSum(ptrs, rows, cols);
        delete[] ptrs;

    } else if (num == 2) {
        int** matrix = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                if (!(in >> matrix[i][j])) {
                    std::cerr << "ERROR: invalid matrix data\n";
                    for (int k = 0; k <= i; ++k) delete[] matrix[k];
                    delete[] matrix;
                    return 2;
                }
            }
        }

        result = findMinSum(matrix, rows, cols);

        for (int i = 0; i < rows; ++i) delete[] matrix[i];
        delete[] matrix;
    }

    out << result << "\n";
    return 0;
}
