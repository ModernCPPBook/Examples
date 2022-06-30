//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CONFIG_HPP
#define CONFIG_HPP


// dependency on gcc snapshot
#include <complex>
#include <string.h>
#include <cmath>

typedef std::complex<double> complex;

// Definiton of constants
const double pi = M_PI;
const size_t max_iteration = 80;
const size_t size_x = 600;
const size_t size_y = 400;
const int max_color = 256;
std::string type;

#endif
