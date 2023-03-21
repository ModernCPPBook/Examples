//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <chrono>

#include "config.hpp"
#include "kernel.hpp"
#include "pbm.hpp"

int main(int argc, char* argv[]) {
  size_t output = get_size_t("OUTPUT", 1);

  //  Defintion of utility
  PBM pbm = PBM(size_x, size_y);

  auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for
  for (size_t i = 0; i < size_x; i++) {
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
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() * 1e-6 << std::endl;

  // Save the image
  if (output == 1) pbm.save("image_parallel_" + type + ".pbm");

  return EXIT_SUCCESS;
}
