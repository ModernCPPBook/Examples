//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <hpx/config.hpp>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>

struct data {
 private:
  typedef hpx::serialization::serialize_buffer<double> buffer_type;

 public:
  data() : size_(0) {}

  data(size_t size)
      : data_(std::allocator<double>().allocate(size), size, buffer_type::take),
        size_(0) {}

  data(size_t size, double* data)
      : data_(std::allocator<double>().allocate(size), size, buffer_type::take),
        size_(size) {
    for (size_t i = 0; i < size_; i++) data_[i] = data[i];
  }

  data(size_t size, double data)
      : data_(std::allocator<double>().allocate(size), size, buffer_type::take),
        size_(size) {
    for (size_t i = 0; i < size_; i++) data_[i] = data;
  }

  double& operator[](size_t id) { return data_[id]; }

  size_t size() { return size_; }

 private:
  buffer_type data_;
  size_t size_;

  friend class hpx::serialization::access;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int) {
    ar& data_& size_;
  }
};

static void square(data d) {
  for (size_t i = 0; i < d.size(); i++) d[i] = d[i] * d[i];
}

HPX_PLAIN_ACTION(square, square_action);

int main(int args, char** argv) {
  data d = data(10, 2.);

  auto remote = hpx ::find_remote_localities();
  if (remote.size() > 0) {
    hpx::future<void> future = hpx::async<square_action>(remote[0], d);
  }
  return EXIT_SUCCESS;
}
