#include <iostream>
int main()
{
  const int min_dlina = 3;
  const int oshibka_1 = 1;
  const int oshibka_2 = 2;
  long long number = 0;
  long long pred1 = 0;
  long long pred2 = 0;
  long long maxnum = 0;
  long long chet12 = 0;
  long long obsh_dlina12 = 0;
  long long chet15 = 0;
  long long obsh_dlina15 = 0;

  while (std::cin >> number) {
    if (number == 0) {
      break;
    }
    obsh_dlina15++;
    obsh_dlina12++;
    if (obsh_dlina12 == 1) {
      maxnum = number;
      chet12 = 0;
    } else {
      if (number > maxnum) {
        maxnum = number;
        chet12 = 0;
      } else {
        chet12++;
      }
    }
    if (obsh_dlina15 >= min_dlina) {
      if ((pred1 + pred2) == number) {
        chet15++;
      }
    }
    pred2 = pred1;
    pred1 = number;
  }

  if (!std::cin && !std::cin.eof()) {
    std::cerr << "oshibka: vvboda\n";
    return oshibka_1;
  }

  bool oshibka = false;

  if (obsh_dlina12 == 0) {
    std::cerr << "oshibka: korotkaya posledovatelnost\n";
    oshibka = true;
  } else {
    std::cout << chet12 << "\n";
  }

  if (obsh_dlina15 < min_dlina) {
    std::cerr << "oshibka: korotkaya posledovatelnost" << "\n";
    oshibka = true;
  } else {
    std::cout << chet15 << "\n";
  }
  if (oshibka == true) {
    return oshibka_2;
  }
  return 0;
}

