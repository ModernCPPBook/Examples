//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <array>
#include <cmath>
#include <cstdlib>
#include <hpx/hpx_main.hpp>
#include <hpx/numeric.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <hpx/parallel/datapar.hpp>

int main(int args, char** argv) {
  std::array<int, 100000> a;

  std::cout << hpx::reduce(hpx::execution::simd, std::begin(a), std::end(a), 0)
            << std::endl;

  std::cout << hpx::reduce(hpx::execution::par_simd, std::begin(a), std::end(a),
                           0)
            << std::endl;

  return EXIT_SUCCESS;
}
