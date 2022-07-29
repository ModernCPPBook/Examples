#include <cmath>
#include <cstdlib>
#include <array>

#include <hpx/hpx_main.hpp>
#include <hpx/algorithms.hpp>

int main(int args, char** argv) {
 
  std::array<int,100000> a;

  hpx::for_loop(hpx::execution::par,0, a.size(), [&](size_t i) {

          a[i] = i * i ;

  });

  return EXIT_SUCCESS;
}
