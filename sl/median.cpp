#include <algorithm>
#include <iostream>
#include <list>

int main() {
  typedef std::list<double>::size_type list_size;
  std::list<double> values;
  double x = 0;

  while (std::cin >> x) {
    values.push_back(x);
  }

  values.sort();
  list_size mid_index = values.size() / 2;
  auto mid = values.begin();
  std::advance(mid, mid_index);

  double median = 0;

  if (values.size() % 2 == 0) {
    auto mid_one = values.begin();
    std::advance(mid_one, mid_index + 1);
    median = 0.5 * (*mid + *mid_one);
  } else
    median = *mid;

  std::cout << "Median: " << median << std::endl;

  return EXIT_SUCCESS;
}
