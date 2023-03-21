//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>

#include "taylor_data.hpp"
#include "taylor_component.hpp"
#include "taylor_action.hpp"


int main(int args, char** argv) {
  int n = std::stoi(argv[1]);
  double x = std::stod(argv[2]);

  std::vector<hpx::id_type> localities = hpx::find_all_localities();
  std::size_t amount = localities.size();

  std::cout << amount << std::endl;

  size_t partitions = std::round(n / amount);

  std::vector<data_client> parts(amount);

  for (size_t i = 0; i < amount; i++) {
    size_t begin = 1;

    if (i > 0) begin = i * partitions;

    if (i == amount - 1)

      parts[i] = data_client(localities[i], n - (partitions * i), begin);

    else

      parts[i] = data_client(localities[i], partitions, begin);
  }

  std::vector<hpx::future<double>> futures;

  for (size_t i = 0; i < amount; i++) {
    futures.push_back(hpx::async<compute_action>(localities[i], parts[i], x));
  }

  if (hpx::find_here() == localities[0]) {
    double result = 0;

    hpx::when_all(futures)
        .then([&](auto&& f) {
          auto futures = f.get();

          for (size_t i = 0; i < futures.size(); i++)
            result += futures[i].get();
        })
        .get();

    std::cout << "Difference of Taylor and C++ result "
              << result - std::log1p(x) << " after " << n << " iterations."
              << std::endl;
  }

  return EXIT_SUCCESS;
}
