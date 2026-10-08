#include <iomanip>
#include <iostream>
#include <stdexcept>

const int MAX_SIZE = 100;

void printMatrix(int m[][MAX_SIZE], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (!(std::cin >> m[i][j])) {
        throw std::invalid_argument("Matrix element must be a number.");
      }

      if (m[i][j] < -100 || m[i][j] > 100) {
        throw std::out_of_range(
            "Matrix element must be between -100 and 100.");
      }
    }
  }

  double sum = 0.0;
  int max = -100;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      sum += m[i][j];

      if (m[i][j] > max) {
        max = m[i][j];
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << std::setw(6) << m[i][j] << " ";
    }
    std::cout << '\n';
  }

  std::cout << sum << '\n';
  std::cout << max << '\n';

  if (rows * cols == 0) {
    throw std::invalid_argument("rows and cols must not be 0.");
  }

  std::cout << sum / (rows * cols) << '\n';

  int cordx, cordy;

  if (!(std::cin >> cordx >> cordy)) {
    throw std::invalid_argument("Coordinates must be numbers.");
  }

  if (cordx >= rows || cordy >= cols || cordx < 0 || cordy < 0) {
    throw std::out_of_range("cords must be between 0 and 100");
  }

  std::cout << m[cordx][cordy] << '\n';
}

void sumMult(int fsNum, int scdNum, int& sum, int& mult) {
  sum = fsNum + scdNum;
  mult = fsNum * scdNum;
}

void reverseString(std::string& str) {
  std::size_t len = str.length();

  for (std::size_t i = 0; i < len / 2; i++) {
    char tmp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = tmp;
  }
}

int main() {
  try {
    int rows, cols;

    std::cin >> rows >> cols;

    if (std::cin.fail()) {
      throw std::invalid_argument("Input error.");
    }

    if (rows < 1 || cols < 1 || rows > MAX_SIZE || cols > MAX_SIZE) {
      throw std::out_of_range("rows and cols must be between 1 and 100");
    }

    int m[MAX_SIZE][MAX_SIZE];

    printMatrix(m, rows, cols);

    std::string str;
    std::cin >> str;

    if (std::cin.fail()) {
      throw std::invalid_argument("Input error.");
    }

    reverseString(str);
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
  } catch (std::out_of_range& e) {
    std::cerr << e.what() << '\n';
  }
}