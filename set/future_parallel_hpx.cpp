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

#include "config.h"
#include "kernel.h"

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

int main(int argc, char* argv[]) {
  size_t partitions = get_size_t("NUM_THREADS", 3);
  size_t output = get_size_t("OUTPUT", 1);

  // Defintion of utility
  PBM pbm = PBM(size_x, size_y);

  size_t size = std::round(size_x / partitions);

  std::vector<hpx::future<void>> futures;

  auto start = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < partitions; i++) {
    size_t start = i * size;
    size_t end = (i + 1) * size;
    if (i == partitions - 1) end = size_x;
    auto f = hpx::async(launch, start, end, &pbm);

    futures.push_back(std::move(f));
  }

  hpx::when_all(futures)
      .then([&](auto&& f) {
        // Save the image
        if (output == 1) pbm.save("image_future_parallel_" + type + ".pbm");
      })
      .get();

  auto stop = std::chrono::high_resolution_clock::now();
  hpx::experimental::for_loop(hpx::execution::par, 0, size_x, [&pbm](size_t i) {
    complex c =
        complex(0, 4) * complex(i, 0) / complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < size_y; j++) {

  return EXIT_SUCCESS;
}
