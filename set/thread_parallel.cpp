//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <pbm.hpp>
#include <thread>

#include "config.h"
#include "kernel.h"

// Function to comoute the Mandelbrot set for a pixel
size_t compute_pixel(complex c) {
  // std::complex<double> z(0, 0);
  for (size_t i = 0; i < max_iteration; i++) {
    if (type == "mandelbrot")
      return mandelbrot(c);
    else
      return julia(c);
  }

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " type nthreads" << std::endl;
    return 0;
  }

  type = argv[1];

  int nthreads = std::stod(argv[2]);

  // Defintion of utility
  PBM pbm = PBM(size_x, size_y);

  std::vector<size_t> index(size_x);
  std::iota(index.begin(), index.end(), 0);

  std::vector<std::thread> threads;
  for (int n = 0; n < nthreads; n++) {
    const int delx = index.size() / nthreads;
    // split into equal chunks
    const int nlo = n * delx;
    const int nhi = n + 1 == nthreads ? index.size() : (n + 1) * delx;
    std::thread t([&]() {
      std::for_each(index.begin() + nlo, index.begin() + nhi, [&pbm](size_t i) {
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
    });
    threads.push_back(std::move(t));
  }
  for (std::thread& t : threads) t.join();

  // Save the image
  pbm.save("image_threads_" + type + ".pbm");

  return EXIT_SUCCESS;
}
