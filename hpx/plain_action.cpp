//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>

static double square(double a) { return a * a; }

// Register the plain action
HPX_PLAIN_ACTION(square, square_action);

int main(int args, char** argv) {
  // C++ standard conform asynchronous function launch
  hpx::future<double> future = hpx::async(square, 10);
  std::cout << future.get() << std::endl;

  // Launch the HPX action locally
  auto id = hpx::find_here();
  future = hpx::async<square_action>(id, 100);
  std::cout << future.get() << std::endl;

  // Launch the HPX action remotely
  auto remote = hpx::find_remote_localities();

  if (remote.size() > 0) {
    future = hpx::async<square_action>(remote[0], 1000);
    std::cout << future.get() << std::endl;
  }

  return EXIT_SUCCESS;
}
