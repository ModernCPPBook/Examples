#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

template <typename T>
std::pair<T, T> slide(T first, T last, T pos) {
  if (pos < first) return {pos, std::rotate(pos, first, last)};

  if (last < pos) return {std::rotate(first, last, pos), pos};

  return {first, last};
}

int main(void) {
  std::vector<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Move elements (0,1,2) to position 6 of the list
  slide<std::vector<int>::iterator>(std::begin(list), std::begin(list) + 3,
                                    std::begin(list) + 6);

  std::for_each(std::begin(list), std ::end(list),
                [](int e) { std::cout << e << std::endl; });

  return EXIT_SUCCESS;
}
