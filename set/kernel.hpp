//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "config.hpp"

// Kernel to compute the Mandelbrot set
inline size_t mandelbrot(complex c) {
  std::complex<double> z(0, 0);
  for (size_t i = 0; i < max_iterations; i++) {
    z = z * z + c;
    if (abs(z) > 2.0) {
      return i;
    }
  }
  return 0;
}

inline double get_double(const char *varname,double defval) {
    const char *strval = getenv(varname);
    double retval;
    if(strval == nullptr) {
        retval = defval;
    } else {
        std::stringstream ss(strval);
        ss >> retval;
    }
    std::cout << "Using " << varname << "=" << retval << std::endl;
    return retval;
}

inline std::complex<double> get_const() {
  return {get_double("C_REAL",-.4),get_double("C_IMAG",.6)};
}

const std::complex<double> julia_const = get_const();

// Kernel to compute the Julia set
inline size_t julia(complex z) {
  for (size_t i = 0; i < max_iterations; i++) {
    z = z * z + julia_const;
    if (abs(z) > 2.0) {
      return i;
    }
  }
  return 0;
}

// Function to comoute the Mandelbrot set for a pixel
inline size_t compute_pixel(complex c) {
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
