#include <iostream>

int main() {
    int num;
    
    if (!(std::cin >> num)) {
        std::cerr << "Error: invalid input format" << std::endl;
        return 1;
    }
    
    if (num == 0) {
        std::cerr << "Error: empty sequence" << std::endl;
        return 2;
    }
    
    int max_val = num;
    int max_count = 1;
    
    int min_val = num;
    int min_count = 1;
    
    while (std::cin >> num) {
        if (num == 0) {
            break;
        }
        
        if (num > max_val) {
            max_val = num;
            max_count = 1;
        } 
        else if (num == max_val) {
            max_count++;
        }
        
        if (num < min_val) {
            min_val = num;
            min_count = 1;
        } 
        else if (num == min_val) {
            min_count++;
        }
    }
    
    if (!std::cin && num != 0) {
        std::cerr << "Error: invalid input inside sequence" << std::endl;
        return 1;
    }
    
    std::cout << max_count << std::endl;
    std::cout << min_count << std::endl;
    
    return 0;
}
