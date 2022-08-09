#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <future>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main(int args, char** argv) {
  int n = std::stoi(argv[1]);
  double x = std::stod(argv[2]);
  size_t amount = std::stoi(argv[3]);

  std::vector<double> parts(n);
  std::iota(parts.begin(), parts.end(), 1);

  size_t partitions = std::round(n / amount);

  std::vector<std::future<double>> futures;
  for (size_t i = 0; i < amount; i++) {
    size_t begin = i * partitions;
    size_t end = (i + 1) * partitions;
    if (i == amount - 1) end = n;

    std::future<double> f = std::async([begin, end, x, &parts]() -> double {
      std::for_each(parts.begin() + begin, parts.begin() + end, [x](double& e) {
        e = std::pow(-1.0, e + 1) * std::pow(x, e) / (e);
      });

      return std::accumulate(parts.begin() + begin, parts.begin() + end, 0.);
    });

    futures.push_back(std::move(f));
  }

  double result = 0;
  for (size_t i = 0; i < futures.size(); i++) result += futures[i].get();

  std::cout << "Difference of Taylor and C++ result "
            << result - std::log(1 + x) << " after " << n << " iterations."
            << std::endl;
  return EXIT_SUCCESS;
}
