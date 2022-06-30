//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

int main(void) {
  double sum = 0;
  size_t count = 0;
  double x = 0;

  while (std::cin >> x) {
    sum += x;
    ++count;
  }

  std::cout << "Average: " << sum / count << std::endl;

  return EXIT_SUCCESS;
}
