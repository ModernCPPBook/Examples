//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>

int main(int args, char** argv) {
  // Get the number of OS threads
  std::cout << hpx::get_os_thread_count() << std::endl;

  // Get the number of all localities
  std::cout << hpx::get_num_localities().get() << std::endl;

  // Get all localities
  std::cout << hpx::find_all_localities().size() << std::endl;

  // Get all remote localities
  std::cout << hpx::find_all_localities().size() << std::endl;

  // Get the global address of the localtiy the function is executed
  hpx::id_type here = hpx::find_here();

  return EXIT_SUCCESS;
}
