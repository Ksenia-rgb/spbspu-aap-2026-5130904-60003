#include <iostream>
int main() {
    const int end_of_sequence = 0;
    const int wrong_type_of_entry = 1;
    const int not_enough_data = 2;
    int previous_entry = 0;
    int pre_previous_entry = 0;
    bool is_there_a_previous_entry = false;
    bool is_there_a_pre_previous_entry = false;
    bool is_the_previous_entry_bigger_than_the_pre_previous_entry = false;
    bool is_the_previous_entry_bigger_than_current_entry = false;
    bool is_the_previous_entry_smaller_than_the_pre_previous_entry = false;
    int entries_that_are_smaller_than_the_previous_entry_and_bigger_than_the_current_entry = 0;
    int entry_count = 0;

    int loc_max_count = 0;
    int entry = 0;
    std::cout<<"Enter your sequence: ";
    while (true) {
        std::cin >> entry;
        if (std::cin.fail()) {
            std::cerr<<"ERROR. INVALID INPUT (Return code: 1)\n";
            return wrong_type_of_entry;
        if (entry == end_of_sequence) {
            if(entry_count < 3) {
                std::cerr<<"ERROR. NOT ENOUGH DATA (Return code: 2)\n";
                return not_enough_data;
            }
            break;
        }
        }
        entry_count++;
        if (entry_count == 1) {
            previous_entry = entry;
            is_there_a_previous_entry = true;
        } else if (entry_count == 2) {
            pre_previous_entry = previous_entry;
            previous_entry = entry;
            is_there_a_pre_previous_entry = true;
        } else {
            is_the_previous_entry_bigger_than_the_pre_previous_entry = previous_entry > pre_previous_entry;
            is_the_previous_entry_bigger_than_current_entry = previous_entry > entry;
            is_the_previous_entry_smaller_than_the_pre_previous_entry = previous_entry < pre_previous_entry;
            if (is_the_previous_entry_bigger_than_the_pre_previous_entry && is_the_previous_entry_bigger_than_current_entry) {
                loc_max_count++;
            }
            if(is_the_previous_entry_smaller_than_the_pre_previous_entry && is_the_previous_entry_bigger_than_current_entry) {
                entries_that_are_smaller_than_the_previous_entry_and_bigger_than_the_current_entry++;
            }
            pre_previous_entry = previous_entry;
            previous_entry = entry;
        }
    }
    std::cout<<"Amount of local maxmimums: " <<loc_max_count<<"\n";
    std::cout<<"Amount of entries that are smaller than the previous entry and bigger than the current entry: " <<entries_that_are_smaller_than_the_previous_entry_and_bigger_than_the_current_entry<<"\n";
    return 0;
}