//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <hpx/future.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/numeric.hpp>
#include <iostream>
#include <pbm.hpp>

#include "config.hpp"
#include "kernel.hpp"

void launch(size_t begin, size_t end, PBM* pbm) {
  for (size_t i = begin; i < end; i++)

  {
    complex c =
        complex(0, 4) * complex(i, 0) / complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < size_y; j++) {
      // Get the number of iterations
      int value = compute_pixel(c + 4.0 * j / size_y - 2.0);
      // Convert the smoothened value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      // Set the pixel color
      (*pbm)(i, j) = make_color(std::get<0>(color), std::get<1>(color),
                                std::get<2>(color));
    }
  }
}

hpx::future<void> run(size_t size, size_t partitions, size_t output, PBM* pbm) {
  std::vector<hpx::future<void>> futures;

  for (size_t i = 0; i < partitions; i++) {
    size_t start = i * size;
    size_t end = (i + 1) * size;
    if (i == partitions - 1) end = size_x;
    auto f = hpx::async(launch, start, end, pbm);

    futures.push_back(std::move(f));
  }

  auto futures2 = co_await hpx::when_all(std::move(futures));

  co_return;
}

int main(int argc, char* argv[]) {
  size_t output = get_size_t("OUTPUT", 1);
  size_t partitions = get_size_t("NUM_THREADS", 3);

  // Defintion of utility
  PBM pbm = PBM(size_x, size_y);

  size_t size = std::round(size_x / partitions);

  auto start = std::chrono::high_resolution_clock::now();

  run(size, partitions, output, &pbm).get();

  auto stop = std::chrono::high_resolution_clock::now();

  if (output == 1) pbm.save("image_future_parallel_" + type + ".pbm");

  return EXIT_SUCCESS;
}
