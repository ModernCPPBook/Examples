//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "config.h"

// Kernel to compute the Mandelbrot set
size_t mandelbrot(complex c) {
  std::complex<double> z(0, 0);
  for (size_t i = 0; i < max_iterations; i++) {
    z = z * z + c;
    if (abs(z) > 2.0) {
      return i;
    }
  }
  return 0;
}

// Kernel to compute the Julia set
size_t julia(complex z) {
  std::complex<double> c(-0.4,0.6);
  for (size_t i = 0; i < max_iterations; i++) {
    z = z * z + c;
    if (abs(z) > 2.0) {
      return i;
    }
  }
  return 0;
}

// Function to comoute the Mandelbrot set for a pixel
size_t compute_pixel(complex c) {
  // std::complex<double> z(0, 0);
  for (size_t i = 0; i < max_iterations; i++) {
    if (type == "mandelbrot")
      return mandelbrot(c);
    else
      return julia(c);
  }

  return 0;
}

#endif
