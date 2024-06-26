#include <array>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/numeric.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <hpx/parallel/datapar.hpp>
//-----------------------------------------------------------------
int main() {
  std::array<int, 100000> a;

  std::cout << hpx::reduce(hpx::execution::simd, std::begin(a), std::end(a), 0) << std::endl; 

  std::cout << hpx::reduce(hpx::execution::par_simd, std::begin(a), std::end(a), 0) << std::endl; 
}
