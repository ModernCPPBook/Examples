#include <cmath>
#include <cstdlib>
#include <hpx/hpx_main.hpp>
#include <hpx/numeric.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <iostream>
#include <string>
#include <vector>

int main(int args, char** argv) {
  int n = std::stoi(argv[1]);
  double x = std::stod(argv[2]);

  std::vector<double> parts(n);
  std::iota(parts.begin(), parts.end(), 1);

  hpx::for_each(
      hpx::execution::par, parts.begin(), parts.end(),
      [x](double& e) { e = std::pow(-1.0, e + 1) * std::pow(x, e) / (e); });

  double result =
      hpx::reduce(hpx::execution::par, parts.begin(), parts.end(), 0.);

  std::cout << "Difference of Taylor and C++ result "
            << result - std::log(1 + x) << " after " << n << " iterations."
            << std::endl;
  return EXIT_SUCCESS;
}
