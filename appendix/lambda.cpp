#include <algorithm>
#include <iostream>
#include <vector>

// Define a named function
void print(int value) { std::cout << value << std::endl; }

int main(void) {
  // Vector to be printed
  std::vector<int> values = {1, 2, 3, 4, 5};

  std::for_each(values.begin(), values.end(), print);

  std::cout << "-------------" << std::endl;

  std::for_each(values.begin(), values.end(),
                [](int value) { std::cout << value << std::endl; });

  return EXIT_SUCCESS;
}
