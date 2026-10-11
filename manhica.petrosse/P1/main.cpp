#include <iostream>
#include <limits>
using namespace std;

void runINCSEQ() {
    int previous, current;
    int count = 0;

    cout << "\n[INC-SEQ] Enter the sequence (0 to stop): ";
    cin >> previous;

    while (previous != 0) {
        cin >> current;

        if (current == 0)
            break;

        if (current > previous)
            count++;

        previous = current;
    }

    cout << "Result: " << count << "\n";
}

void runPTHTRP() {
    int a, b, c;
    int count = 0;

    cout << "\n[PTH-TRP] Enter the sequence (0 to stop): ";
    cin >> a;

    if (a != 0) {
        cin >> b;

        while (b != 0) {
            cin >> c;

            if (c == 0)
                break;

            if (a * a + b * b == c * c)
                count++;

            a = b;
            b = c;
        }
    }

    cout << "Result: " << count << "\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== SEQUENCE ANALYZER =====\n";
        cout << "1. INC-SEQ\n";
        cout << "13. PTH-TRP\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            runINCSEQ();
            break;

        case 13:
            runPTHTRP();
            break;

        case 0:
            cout << "Program terminated.\n";
            break;

        default:
            cout << "Invalid option. Choose 1, 13, or 0.\n";
        }

    } while (choice != 0);

    return 0;
}
