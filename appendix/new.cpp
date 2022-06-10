//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>

int main(void) {
  // Usage of the new expression to generate an array of integers
  int* values = new int[5];

  // Usage of the placement new for struct and classes
  struct vector {
    double x, y, z;

    vector(double x0 = 0, double y0 = 0, double z0 = 0) {
      x = x0;
      y = y0;
      z = z0;
    }
  };

  vector* vec = new vector();

  // Releasing the allocate double array
  delete[] values;

  // Releasing the allocated struct
  delete vec;

  return EXIT_SUCCESS;
}
