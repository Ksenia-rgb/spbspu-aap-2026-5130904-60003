#include <iostream>
int main() {
  const int end_of_sequence = 0;
  const int wrong_type_of_ent = 1;
  const int not_enough_data = 2;
  int prev_ent = 0;
  int pre_prev_ent = 0;
  bool is_prev_ent = false;
  bool is_a_pre_prev_ent = false;
  bool is_prev_ent_bigger_pre_prev_ent = false;
  bool is_prev_ent_bigger_current_ent = false;
  bool is_prev_ent_smaller_pre_prev_ent = false;
  int enties_smaller_prev_ent_and_bigger_cur_ent = 0;
  int ent_count = 0;

  int loc_max_count = 0;
  int ent = 0;
  std::cout << "Enter your sequence: ";
  while (true) {
    std::cin >> ent;
    if (std::cin.fail()) {
      std::cerr << "ERROR. INVALID INPUT (Return code: 1)\n";
      return wrong_type_of_ent;
      if (ent == end_of_sequence) {
        if (ent_count < 3) {
          std::cerr << "ERROR. NOT ENOUGH DATA (Return code: 2)\n";
          return not_enough_data;
        }
        break;
      }
    }
    ent_count++;
    if (ent_count == 1) {
      prev_ent = ent;
      is_prev_ent = true;
    } else if (ent_count == 2) {
      pre_prev_ent = prev_ent;
      prev_ent = ent;
      is_a_pre_prev_ent = true;
    } else {
      is_prev_ent_bigger_pre_prev_ent = prev_ent > pre_prev_ent;
      is_prev_ent_bigger_current_ent = prev_ent > ent;
      is_prev_ent_smaller_pre_prev_ent = prev_ent < pre_prev_ent;
      if (is_prev_ent_bigger_pre_prev_ent && is_prev_ent_bigger_current_ent) {
        loc_max_count++;
      }
      if (is_prev_ent_smaller_pre_prev_ent && is_prev_ent_bigger_current_ent) {
        enties_smaller_prev_ent_and_bigger_cur_ent++;
      }
      pre_prev_ent = prev_ent;
      prev_ent = ent;
    }
  }
  std::cout << "First Answer: " << loc_max_count << "\n";
  std::cout << "Second answer: " << enties_smaller_prev_ent_and_bigger_cur_ent
            << "\n";
  return 0;
}