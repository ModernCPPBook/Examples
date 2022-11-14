//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <vector>

int main(int argc, char* argv[]) {
  size_t size = std::stoi(argv[1]);

  std::vector<double> vec(size);
  std::list<double> list(size);
  std::cout << size << " ";

  auto start = std::chrono::high_resolution_clock::now();
  std::fill(vec.begin(), vec.end(), 1);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  start = std::chrono::high_resolution_clock::now();
  std::fill(list.begin(), list.end(), 1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  start = std::chrono::high_resolution_clock::now();
  vec.push_back(1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  start = std::chrono::high_resolution_clock::now();
  list.push_back(1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<size_t> dist(0, size);

  size_t index = dist(rng);

  start = std::chrono::high_resolution_clock::now();
  vec.insert(vec.begin(), index, 1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  start = std::chrono::high_resolution_clock::now();
  list.insert(list.begin(), index, 1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  index = dist(rng);

  start = std::chrono::high_resolution_clock::now();
  vec.erase(vec.begin() + index, vec.begin() + index + 1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  auto begin = list.begin();
  auto end = list.begin();

  start = std::chrono::high_resolution_clock::now();
  std::advance(begin, index);
  std::advance(end, index + 1);
  list.erase(begin, end);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  index = dist(rng);

  start = std::chrono::high_resolution_clock::now();
  auto result = vec[index];
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << " ";

  start = std::chrono::high_resolution_clock::now();
  begin = list.begin();
  std::advance(begin, index);
  result = *begin;
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << duration.count() << std::endl;
}
