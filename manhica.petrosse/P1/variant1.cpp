#include <iostream>
#include <limits>

int main() {
    long long current = 0;
    long long previous = 0;
    bool hasPrevious = false;
    bool seenZero = false;
    long long count = 0;

    while (std::cin >> current) {
        if (current == 0) {
            seenZero = true;
            break;
        }

        if (!hasPrevious) {
            previous = current;
            hasPrevious = true;
            continue;
        }

        if (current > previous) {
            ++count;
        }

        previous = current;
    }

    // Se a leitura falhou antes de encontrar 0, entao a entrada nao e uma sequencia valida
    if (!seenZero) {
        std::cerr << "Error: invalid input sequence\n";
        return 1;
    }

    std::cout << count << '\n';
    return 0;
}
