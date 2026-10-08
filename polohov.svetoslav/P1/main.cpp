#include <iostream>

const int MAX_NUM = 100;

int length_of_seq() {
  int length_arr = 0;
  int arr[MAX_NUM];
  int length = 0;
  bool zero_found = false;
  int error_code = 0;

  for (int i = 0; i < MAX_NUM; i++) {
    if (!(std::cin >> arr[i])) {
      std::cerr << "Invalid input\n";
      return 1;
    }

    if (arr[i] == 0) {
      zero_found = true;
      break;
    }

    length_arr++;
  }

  if (!zero_found) {
    std::cerr << "Sequence is too long\n";
    return 1;
  }

  if (length_arr == 0) {
    std::cerr << "Cannot calculate decreasing fragment length\n";
    error_code = 2;
  } else {
    for (int i = 0; i < length_arr; i++) {
      int temp = 1;

      for (int j = i; j < length_arr - 1; j++) {
        if (arr[j] < arr[j + 1]) {
          break;
        }

        temp++;
      }

      if (temp > length) {
        length = temp;
      }
    }

    std::cout << length << "\n";
  }

  int num_of_ops = 0;

  for (int j = 0; j < length_arr - 1; j++) {
    if ((arr[j] > 0 && arr[j + 1] < 0) ||
        (arr[j] < 0 && arr[j + 1] > 0)) {
      num_of_ops++;
    }
  }

  std::cout << num_of_ops << "\n";

  return error_code;
}

int main() {
  return length_of_seq();
}
