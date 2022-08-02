#include <array>
#include <cmath>
#include <cstdlib>
#include <hpx/parallel/algorithm.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/numeric.hpp>

int main(int args, char** argv) {
  std::array<int, 100000> a;

  hpx::future<void> f = hpx::for_loop(hpx::execution::par(hpx::execution::task),
                                      0, a.size(), [&](size_t i) {
                                        a[i] = i * i;
                                      });

  f.then([a](auto&& f) {
    std::cout << hpx::reduce(std::begin(a), std::end(a), 0) << std::endl;
  });

  return EXIT_SUCCESS;
}
