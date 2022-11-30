# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_hpx_executable(taylor_hpx SOURCES taylor_hpx.cpp)
add_test(NAME "HPX:_Taylor" COMMAND taylor_hpx 100 0.5)

add_hpx_executable(taylor_hpx_future SOURCES taylor_hpx_future.cpp)
add_test(NAME "HPX:_Taylor_future" COMMAND taylor_hpx_future 100 0.5 3)

add_hpx_executable(taylor_hpx_future_dataflow SOURCES taylor_hpx_future_dataflow.cpp)
add_test(NAME "HPX:_Taylor_future_dataflow" COMMAND taylor_hpx_future_dataflow 100 0.5 3)

add_hpx_executable(taylor_hpx_future_unwrap SOURCES taylor_hpx_future_unwrap.cpp)
add_test(NAME "HPX:_Taylor_future_unwrap" COMMAND taylor_hpx_future_unwrap 100 0.5 3)

add_hpx_executable(parallel_for SOURCES parallel_for.cpp)
add_test(NAME "HPX:_Parallel_for" COMMAND parallel_for)

add_hpx_executable(parallel_for_chunk SOURCES parallel_for_chunk.cpp)
add_test(NAME "HPX:_Parallel_for_with_chunk_size" COMMAND parallel_for_chunk)

add_hpx_executable(parallel_for_async SOURCES parallel_for_async.cpp)
add_test(NAME "HPX:_Parallel_for_async" COMMAND parallel_for_async)

add_hpx_executable(topology SOURCES topology.cpp)
add_test(NAME "HPX:_topology" COMMAND topology)

add_hpx_executable(plain_action SOURCES plain_action.cpp)
add_test(NAME "HPX:_plain_action" COMMAND plain_action)

add_hpx_executable(serialization SOURCES serialization.cpp)
add_test(NAME "HPX:_serialization" COMMAND serialization)

add_hpx_executable(taylor_hpx_distributed SOURCES taylor_hpx_distributed.cpp)
add_test(NAME "HPX:_Taylor_distributed" COMMAND taylor_hpx_distributed)

if(${WITH_COROUTINES})
  #add_hpx_executable(taylor_hpx_future_coroutine SOURCES taylor_hpx_future_coroutine.cpp)
  add_test(NAME "HPX:_Taylor_future_coroutine" COMMAND taylor_hpx_future_coroutine 100 0.5 3)
endif()

if(${WITH_SIMD})
  add_hpx_executable(parallel_reduce_simd SOURCES parallel_reduce_simd.cpp)
add_test(NAME "HPX:_Parallel_reduce_SIMD" COMMAND parallel_reduce_simd)
endif()


