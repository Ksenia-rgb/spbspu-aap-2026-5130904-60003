#include <iostream>
namespace {
  const int min_dlina = 3;
  const int oshibka_1 = 1;
  const int oshibka_2 = 2;
}
int main()
{
  long long number = 0;
  long long pred1 = 0;
  long long pred2 = 0;
  long long maxnum = 0;
  long long chet12 = 0;
  long long obsh_dlina = 0;
  long long chet15 = 0;

  while (std::cin >> number) {
    if (number == 0) {
      break;
    }
    obsh_dlina++;
    if (obsh_dlina == 1) {
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
    if (obsh_dlina >= min_dlina) {
      if ((pred1 + pred2) == number) {
        chet15++;
      }
    }
    pred2 = pred1;
    pred1 = number;
  }

  if (!std::cin && !std::cin.eof()) {
    std::cerr << "oshibka: vvoda\n";
    return oshibka_1;
  }

  bool oshibka = false;

  if (obsh_dlina == 0) {
    std::cerr << "oshibka: korotkaya posledovatelnost\n";
    oshibka = true;
  } else {
    std::cout << chet12 << "\n";
  }

  if (obsh_dlina < min_dlina) {
    std::cerr << "oshibka: korotkaya posledovatelnost" << "\n";
    oshibka = true;
  } else {
    std::cout << chet15 << "\n";
  }
  if (oshibka) {
    return oshibka_2;
  }
  return 0;
}

