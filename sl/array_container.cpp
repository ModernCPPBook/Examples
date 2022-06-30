//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

int main(void) {
  // Define the length of the array
  std::array<double, 6> array;

  // Fill the array
  std::iota(array.begin(), array.end(), 0);

  // Print the array
  std::for_each(array.begin(), array.end(),
                [](double value) { std::cout << value << std::endl; });
}