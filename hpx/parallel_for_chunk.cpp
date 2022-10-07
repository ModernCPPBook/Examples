#include <array>
#include <cmath>
#include <cstdlib>
#include <hpx/hpx_main.hpp>
#include <hpx/parallel/algorithm.hpp>

int main(int args, char** argv) {
  std::array<int, 100000> a;

  // Static chunk size
  hpx::execution::static_chunk_size scs(10);
  hpx::experimental::for_loop(hpx::execution::par.with(scs), 0, a.size(),
                [&](size_t i) { a[i] = i * i; });

  hpx::execution::dynamic_chunk_size dcs(10);
  hpx::experimental::for_loop(hpx::execution::par.with(dcs), 0, a.size(),
                [&](size_t i) { a[i] = i * i; });

  return EXIT_SUCCESS;
}
