//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>
#include <vector>

int main(void) {
  std::string name = "Parallel C++";
  std::vector<std::string> values;

  // Copy the object name to the end of the vector
  values.push_back(name);

  std::cout << "The content of name after copying is " << name << std::endl;

  // Move the object name to the end of the vector
  values.push_back(std::move(name));

  std::cout << "The content of name after moving is " << name << std::endl;
}
