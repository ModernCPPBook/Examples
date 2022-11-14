//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/local/execution.hpp>
#include <hpx/modules/compute.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <pbm.hpp>
#include <vector>

#include "config.h"
#include "kernel.h"

// block executors and allocators are designed to work with NUMA arrays
using executor_type = hpx::compute::host::block_executor<>;
using allocator_type = hpx::compute::host::block_allocator<std::vector<int>>;
using PBM_numa = PBM_<hpx::compute::vector<std::vector<int>, allocator_type>>;

int main(int argc, char* argv[]) {
  size_t output = get_size_t("OUTPUT", 1);

  auto numa_nodes = hpx::compute::host::numa_domains();
  std::cout << "numa_nodes: " << numa_nodes.size() << std::endl;
  allocator_type alloc(numa_nodes);
  executor_type exec(numa_nodes);
  auto policy = hpx::execution::par.on(exec);

  //  Defintion of utility
  PBM_numa pbm(size_x, size_y, alloc);
  // Reallocate vectors on numa domains
  hpx::experimental::for_loop(policy, 0, pbm.width(),
                              [&pbm](size_t i) { pbm.alloc_column(i); });

  auto start = std::chrono::high_resolution_clock::now();

  hpx::experimental::for_loop(policy, 0, pbm.width(), [&pbm](size_t i) {
    complex c =
        complex(0, 4) * complex(i, 0) / complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < pbm.height(); j++) {
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
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() * 1e-6 << std::endl;

  // Save the image
  if (output == 1) pbm.save("image_parallel_" + type + ".pbm");

  return EXIT_SUCCESS;
}
