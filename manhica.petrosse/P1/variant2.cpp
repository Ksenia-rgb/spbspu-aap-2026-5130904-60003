#include <iostream>

bool isPythagorean(long long a, long long b, long long c) {
    // Ordena os numeros para verificar a? + b? = c?
    long long sides[3] = {a, b, c};
    
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (sides[i] > sides[j]) {
                long long temp = sides[i];
                sides[i] = sides[j];
                sides[j] = temp;
            }
        }
    }
    
    return (sides[0] * sides[0] + sides[1] * sides[1] == sides[2] * sides[2]);
}

int main() {
    long long num1 = 0;
    long long num2 = 0;
    long long num3 = 0;
    bool seenZero = false;
    long long count = 0;
    int position = 0;

    long long current;
    while (std::cin >> current) {
        if (current == 0) {
            seenZero = true;
            break;
        }

        num1 = num2;
        num2 = num3;
        num3 = current;
        position++;

        // Se temos pelo menos 3 numeros, verificar se formam um trio pitagorico
        if (position >= 3) {
            if (isPythagorean(num1, num2, num3)) {
                ++count;
            }
        }
    }

    // Se a leitura falhou antes de encontrar 0, entao a entrada nao e uma sequencia valida
    if (!seenZero) {
        std::cerr << "Error: invalid input sequence\n";
        return 1;
    }

    std::cout << count << '\n';
    return 0;
}
