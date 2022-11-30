//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>

struct data {
  data() : size_(0) {}

  data(size_t size)
      : data_(std ::allocator<double>().allocate(size), size,
              buffer_type ::take),
        size_(0) {}

  data(size_t size, double init)
      : data_(std ::allocator<double>().allocate(size), size,
              buffer_type ::take),
        size_(size) {
    for (size_t i = 0; i < size_; i++) data_[i] = init + i;
  }

  size_t size() { return size_; }

  double& operator[](size_t id) { return data_[id]; }

 private:
  typedef hpx ::serialization ::serialize_buffer<double> buffer_type;

  buffer_type data_;
  size_t size_;

  friend class hpx::serialization::access;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int) {
    ar& data_& size_;
  }
};

// Component server

struct data_server : hpx::components::component_base<data_server> {
  // Construct a new instance
  data_server() {}

  data_server(size_t size, double const value) : data_(size, value) {}

  // Access data
  data get_data() const { return data_; }

  HPX_DEFINE_COMPONENT_DIRECT_ACTION(data_server, get_data, get_data_action)

 private:
  data data_;
};

typedef hpx::components::component<data_server> data_server_type;
HPX_REGISTER_COMPONENT(data_server_type, data_server)

typedef data_server::get_data_action get_data_action;
HPX_REGISTER_ACTION(get_data_action)

// Component client

struct data_client : hpx ::components ::client_base<data_client, data_server> {
  typedef hpx::components::client_base<data_client, data_server> base_type;

  data_client() {}

  data_client(hpx::id_type where, size_t size, double init)
      : base_type(hpx::new_<data_server>(where, size, init)) {}
};

int main(int args, char** argv) {
  int n = std::stoi(argv[1]);
  double x = std::stod(argv[2]);

  std::vector<hpx::id_type> localities = hpx::find_all_localities();
  std::size_t amount = localities.size();

  size_t partitions = std::round(n / amount);

  std::vector<data_client> parts(amount);

  for (size_t i = 0; i < amount; i++) {
    size_t begin = i * partitions;

    if (i == amount - 1)

      parts[i] = data_client(localities[i], n, begin);

    else

      parts[i] = data_client(localities[i], partitions, begin);
  }

  /**
  std::vector<double> parts(n);
  std::iota(parts.begin(), parts.end(), 1);

  size_t partitions = std::round(n / amount);

  std::vector<hpx::future<double>> futures;
  for (size_t i = 0; i < amount; i++) {
    size_t begin = i * partitions;
    size_t end = (i + 1) * partitions;
    if (i == amount - 1) end = n;

    hpx::future<double> f = hpx::async([begin, end, x, &parts]() -> double {
      std::for_each(parts.begin() + begin, parts.begin() + end, [x](double& e) {
        e = std::pow(-1.0, e + 1) * std::pow(x, e) / (e);
      });

      return hpx::reduce(parts.begin() + begin, parts.begin() + end, 0.);
    });

    futures.push_back(std::move(f));
  }

  double result = 0;

  hpx::when_all(futures)
      .then([&](auto&& f) {
        auto futures = f.get();

        for (size_t i = 0; i < futures.size(); i++) result += futures[i].get();
      })
      .get();

  std::cout << "Difference of Taylor and C++ result " << result - std::log1p(x)
            << " after " << n << " iterations." << std::endl;

  */
  return EXIT_SUCCESS;
}
