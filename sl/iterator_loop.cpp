//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <iostream>
#include <list>

int main(void) {
  std::list<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Accessing the iterator to the first element
  std::list<int>::iterator it = std::begin(values);

  for (; it != std::end(values); ++it)
    // Accessing the element using the dereference operator *
    std::cout << *it << std::endl;

  std::cout << "------" << std::endl;

  for (const int value : values) std::cout << value << std::endl;

  std::cout << "------" << std::endl;

  for (int index = 0; const int value : values) std::cout << value << std::endl;

  return EXIT_SUCCESS;
}
