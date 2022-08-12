# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_hpx_executable(taylor_hpx SOURCES taylor_hpx.cpp)
add_test(NAME "HPX Taylor" COMMAND taylor_hpx 100 0.5)

add_hpx_executable(taylor_hpx_future SOURCES taylor_hpx_future.cpp)
add_test(NAME "HPX Taylor future" COMMAND taylor_hpx_future 100 0.5 3)

add_hpx_executable(taylor_hpx_future_dataflow SOURCES taylor_hpx_future_dataflow.cpp)
add_test(NAME "HPX Taylor future dataflow" COMMAND taylor_hpx_future_dataflow 100 0.5 3)

add_hpx_executable(taylor_hpx_future_unwrap SOURCES taylor_hpx_future_unwrap.cpp)
add_test(NAME "HPX Taylor future unwrap" COMMAND taylor_hpx_future_unwrap 100 0.5 3)

add_hpx_executable(parallel_for SOURCES parallel_for.cpp)
add_test(NAME "HPX Parallel for" COMMAND parallel_for)

add_hpx_executable(parallel_for_async SOURCES parallel_for_async.cpp)
add_test(NAME "HPX Parallel for async" COMMAND parallel_for_async)
