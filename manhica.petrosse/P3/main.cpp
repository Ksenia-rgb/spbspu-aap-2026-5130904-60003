#include <iostream>
#include <vector>

int main() {
    int rows, cols;
    if (!(std::cin >> rows >> cols)) {
        return 0;
    }

    if (rows <= 0 || cols <= 0 || rows != cols) {
        std::cout << "false\n";
        return 0;
    }

    std::vector<std::vector<long long>> matrix(rows, std::vector<long long>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                return 0;
            }
        }
    }

    bool upperTriangular = true;

    for (int i = 1; i < rows; ++i) {
        for (int j = 0; j < i; ++j) {
            if (matrix[i][j] != 0) {
                upperTriangular = false;
                break;
            }
        }
        if (!upperTriangular) {
            break;
        }
    }

    std::cout << (upperTriangular ? "true" : "false") << '\n';
    return 0;
}
