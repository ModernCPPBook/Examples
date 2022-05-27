//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cmath>
#include <iostream>
#include <vector>

int main(void) {
  std::vector<int> values = {0, 1, 2, 3, 4, 5, 6};

  for (int i : values) {
    if (i % 2 == 0) {
      std::cout << std::sqrt(i) << " ";
    }
  }
}
