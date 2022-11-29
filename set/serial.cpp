//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>
#include <numeric>
#include <pbm.hpp>
#include <chrono>

#include "config.h"
#include "kernel.h"

int main(int argc, char* argv[]) {
  // Defintion of utility
  PBM pbm = PBM(size_x, size_y);

  std::vector<size_t> index(size_x);
  std::iota(index.begin(), index.end(), 0);

  auto start = std::chrono::high_resolution_clock::now();

  std::for_each(index.begin(), index.end(), [&pbm](size_t i) {
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
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() * 1e-6 << std::endl;

  // Save the image
  pbm.save("image_serial_" + type + ".pbm");

  return EXIT_SUCCESS;
}
