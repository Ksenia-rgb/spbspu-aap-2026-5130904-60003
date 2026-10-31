#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>

namespace annageldiyev {

    void processMatrix(int* matrix, int rows, int cols, std::ostream& out) {
        int* original = new int[rows * cols];
        for (int i = 0; i < rows * cols; ++i) {
            original[i] = matrix[i];
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                double sum = 0;
                int count = 0;

                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr == 0 && dc == 0) continue;
                        
                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                            sum += original[nr * cols + nc];
                            count++;
                        }
                    }
                }

                double avg = (count > 0) ? (sum / count) : 0.0;
                
                if (std::abs(avg - std::round(avg)) < 1e-9) {
                    out << std::round(avg);
                } else {
                    out << std::fixed << std::setprecision(1) << avg;
                }
                
                if (!(r == rows - 1 && c == cols - 1)) {
                    out << " ";
                }
            }
        }
        out << "\n";
        delete[] original;
    }

}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments.\n";
        return 1;
    }

    int mode = 0;
    if (std::strcmp(argv[1], "1") == 0) {
        mode = 1;
    } else if (std::strcmp(argv[1], "2") == 0) {
        mode = 2;
    } else {
        std::cerr << "Error: First argument must be 1 or 2.\n";
        return 1;
    }

    std::ifstream inFile(argv[2]);
    if (!inFile.is_open()) {
        std::cerr << "Error: Cannot open input file.\n";
        return 2;
    }

    int rows = 0, cols = 0;
    if (!(inFile >> rows >> cols)) {
        std::cerr << "Error: Cannot read matrix dimensions.\n";
        return 2;
    }

    if (rows <= 0 || cols <= 0) {
        std::cerr << "Error: Invalid matrix dimensions.\n";
        return 2;
    }

    std::ofstream outFile(argv[3]);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open output file.\n";
        return 2;
    }

    outFile << rows << " " << cols << " ";

    if (mode == 1) {
        if (rows * cols > 10000) {
            std::cerr << "Error: Matrix too large for stack.\n";
            return 2;
        }
        int matrix[10000];
        for (int i = 0; i < rows * cols; ++i) {
            if (!(inFile >> matrix[i])) {
                std::cerr << "Error: Not enough matrix elements.\n";
                return 2;
            }
        }
        annageldiyev::processMatrix(matrix, rows, cols, outFile);
    } else {
        int* matrix = new int[rows * cols];
        for (int i = 0; i < rows * cols; ++i) {
            if (!(inFile >> matrix[i])) {
                std::cerr << "Error: Not enough matrix elements.\n";
                delete[] matrix;
                return 2;
            }
        }
        annageldiyev::processMatrix(matrix, rows, cols, outFile);
        delete[] matrix;
    }

    return 0;
}
