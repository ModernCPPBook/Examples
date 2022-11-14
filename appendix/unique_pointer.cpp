//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <stdlib.h>

#include <memory>

int main(void) {
  std::unique_ptr<double[]> a(new double[2]);

  // Initialize the values
  a[0] = 1;
  a[1] = 2;

  // Generate a copy of the array a
  // std::unique_ptr<double[]>b(a);

  // Generate a copy of the array a
  std ::unique_ptr<double[]> b(std ::move(a));

  return EXIT_SUCCESS;
}
