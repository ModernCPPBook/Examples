#include <cmath>
#include <iostream>
#include <ranges>
#include <vector>
//-----------------------------------------------------------------
int main() {
  std ::vector<int> values = {0, 1, 2, 3, 4, 5, 6};

  auto tr_values = values
    |  std::views::filter([](int value) { return value % 2 == 0; }) 
    |  std::views::transform([](int value) -> double { return std::sqrt(value);});
  for (int i : tr_values)
      std::cout << double(i) << ' ';
  std::cout << std::endl;
}
