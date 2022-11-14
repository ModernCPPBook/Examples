//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

int main(int args, char** argv) {
  int n = std::stoi(argv[1]);
  double x = std::stod(argv[2]);
  size_t amount = std::stoi(argv[3]);

  std::vector<double> parts(n);
  std::iota(parts.begin(), parts.end(), 1);

  size_t partitions = std::round(n / amount);

  std::vector<std::thread> threads;
  for (size_t i = 0; i < amount; i++) {
    size_t begin = i * partitions;
    size_t end = (i + 1) * partitions;
    if (i == amount - 1) end = n;

    std::thread t([begin, end, x, &parts]() {
      std::for_each(parts.begin() + begin, parts.begin() + end, [x](double& e) {
        e = std::pow(-1.0, e + 1) * std::pow(x, e) / (e);
      });
    });

    threads.push_back(std::move(t));
  }

  for (std::thread& t : threads) t.join();

  double result = std::accumulate(parts.begin(), parts.end(), 0.);

  std::cout << "Difference of Taylor and C++ result " << result - std::log1p(x)
            << " after " << n << " iterations." << std::endl;
  return EXIT_SUCCESS;
}
