//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <list>
#include <vector>

int main(void) {
  std::vector<double> vec = {1, 2, 3, 4, 5, 6};
  std::list<double> lis = {1, 2, 3, 4, 5, 6};

  std::cout << vec[3] << std::endl;

  std::list<double>::iterator begin = std::begin(lis);
  std::advance(begin, 3);

  std::cout << *begin << std::endl;

  return EXIT_SUCCESS;
}
