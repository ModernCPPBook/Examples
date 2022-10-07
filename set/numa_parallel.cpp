/*
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/local/execution.hpp>

#include <hpx/modules/compute.hpp>
#include <hpx/modules/compute_local.hpp>

#include <vector>

// block executors and allocators are designed to work with NUMA arrays
using executor_type = hpx::compute::host::block_executor<>;
using allocator_type = hpx::compute::host::block_allocator<double>;
using vector_type = hpx::compute::vector<double, allocator_type>;

template<typename Policy>
void update_heat(vector_type& v_old, vector_type& v_new,vector_type& err,Policy policy) {
    const auto sz = v_new.size()-1;
    hpx::experimental::for_loop(policy, 1, sz, [&](auto i) {
        v_new[i] = 0.5*(v_old[i+1] + v_old[i-1]);
    });
    hpx::experimental::for_loop(policy, 1, sz, [&](auto i) {
        err[i] = fabs(v_new[i] - v_old[i]);
        v_old[i] = v_new[i];
    });
}

int main() {
    auto numa_nodes = hpx::compute::host::numa_domains();
    allocator_type alloc(numa_nodes);
    executor_type exec(numa_nodes);
    auto policy = hpx::execution::par.on(exec);

    const std::size_t sz = 1000;
    const std::size_t time_steps = 100;

    vector_type data_new(sz, alloc);
    vector_type data_old(sz, alloc);
    vector_type err(sz, alloc);

    // initial data
    hpx::fill(policy, data_old.begin(), data_old.end(), 1.0);
    data_old[0] = 0;
    data_old[sz-1] = 100;
    err[0] = 0;
    err[sz-1] = 0;

    for(int tm=0;tm <= time_steps;++tm) {
        update_heat(data_old, data_new, err, policy);
        
        auto max_i = hpx::max_element(policy,err.begin(),err.end());
        std::cout << tm << " " << *max_i << std::endl;
    }
}
*/
//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <pbm.hpp>

#include <hpx/local/execution.hpp>
#include <hpx/modules/compute.hpp>
//#include <hpx/modules/compute_local.hpp>

#include <vector>

#include "config.h"
#include "kernel.h"

// block executors and allocators are designed to work with NUMA arrays
using executor_type = hpx::compute::host::block_executor<>;
using allocator_type = hpx::compute::host::block_allocator<std::vector<int>>;
using PBM_numa = PBM_<hpx::compute::vector<std::vector<int>, allocator_type>>;

int main(int argc, char* argv[]) {
  size_t output = get_size_t("OUTPUT", 1);

  //  Defintion of utility
  PBM_numa pbm(size_x, size_y);

  auto numa_nodes = hpx::compute::host::numa_domains();
  allocator_type alloc(numa_nodes);
  executor_type exec(numa_nodes);
  auto policy = hpx::execution::par.on(exec);

  auto start = std::chrono::high_resolution_clock::now();
  hpx::experimental::for_loop(policy, 0, size_x, [&pbm](size_t i) {
    complex c =
        complex(0, 4) * complex(i, 0) / complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < size_y; j++) {
      // Get the number of iterations
      int value = compute_pixel(c + 4.0 * j / size_y - 2.0);
      // Convert the smoothened value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      // Set the pixel color
      pbm(i, j) = make_color(std::get<0>(color), std::get<1>(color),
                             std::get<2>(color));
    }
  });
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(stop - start);
  std::cout << duration.count() << std::endl;

  // Save the image
  if (output == 1) pbm.save("image_parallel_" + type + ".pbm");

  return EXIT_SUCCESS;
}
