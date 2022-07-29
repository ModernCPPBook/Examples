# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_hpx_executable(taylor_hpx SOURCES taylor_hpx.cpp)
add_test(NAME "HPX Taylor" COMMAND taylor_hpx 100 0.5)

add_hpx_executable(parallel_for SOURCES parallel_for.cpp)
add_test(NAME "HPX Parallel for" COMMAND parallel_for)
