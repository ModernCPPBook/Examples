#include <cmath>
#include <cstdlib>
#include <hpx/hpx_main.hpp>
#include <hpx/numeric.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

hpx::future<double> run(size_t n, size_t amount, double x) {
  std::vector<double> parts(n);
  std::iota(parts.begin(), parts.end(), 1);

  size_t partitions = std::round(n / amount);

  std::vector<hpx::future<double>> futures;
  for (size_t i = 0; i < amount; i++) {
    size_t begin = i * partitions;
    size_t end = (i + 1) * partitions;
    if (i == amount - 1) end = n;

    hpx::future<double> f = hpx::async([begin, end, x, &parts]() -> double {
      std::for_each(parts.begin() + begin, parts.begin() + end, [x](double& e) {
        e = std::pow(-1.0, e + 1) * std::pow(x, e) / (e);
      });

      return hpx::reduce(parts.begin() + begin, parts.begin() + end, 0.);
    });

    futures.push_back(std::move(f));
  }

  double result = 0;

  auto futures2 = co_await hpx::when_all(futures);

  for (size_t i = 0; i < futures2.size(); i++) result += co_await futures2[i];

  co_return result;
}

int main(int args, char** argv) {
  int n = std::stoi(argv[1]);
  double x = std::stod(argv[2]);
  size_t amount = std::stoi(argv[3]);

  double result = run(n, amount, x).get();
  std::cout << "Difference of Taylor and C++ result " << result - std::log1p(x)
            << " after " << n << " iterations." << std::endl;
  return EXIT_SUCCESS;
}
