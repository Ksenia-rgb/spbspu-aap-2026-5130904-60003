#include <iostream>

const int MAX_NUM = 100;

int lengthOfSeq() {
  int lengthArr = 0;
  int arr[MAX_NUM];
  int length = 0;
  bool zeroFound = false;
  int errorCode = 0;

  for (int i = 0; i < MAX_NUM; i++) {
    if (!(std::cin >> arr[i])) {
      std::cerr << "Invalid input\n";
      return 1;
    }

    if (arr[i] == 0) {
      zeroFound = true;
      break;
    }

    lengthArr++;
  }

  if (!zeroFound) {
    std::cerr << "Sequence is too long\n";
    return 1;
  }

  if (lengthArr == 0) {
    std::cerr << "Cannot calculate decreasing fragment length\n";
    errorCode = 2;
  } else {
    for (int i = 0; i < lengthArr; i++) {
      int temp = 1;

      for (int j = i; j < lengthArr - 1; j++) {
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

  int numOfOps = 0;

  for (int j = 0; j < lengthArr - 1; j++) {
    if ((arr[j] > 0 && arr[j + 1] < 0)
        || (arr[j] < 0 && arr[j + 1] > 0)) {
      numOfOps++;
    }
  }

  std::cout << numOfOps << "\n";

  return errorCode;
}

int main() {
  return lengthOfSeq();
}
