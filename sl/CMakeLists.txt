# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_executable(average average.cpp)

add_executable(array_language array_language.cpp)
add_test(NAME "SL: Array language" COMMAND array_language)

add_executable(array_container array_container.cpp)
add_test(NAME "SL: Array container" COMMAND array_container)

add_executable(benchmark_containers benchmark_containers.cpp)
add_test(NAME "SL: Benchmark containers" COMMAND benchmark_containers 100)

add_executable(median median.cpp)

add_executable(iterator_loop iterator_loop.cpp)
add_test(NAME "SL: iterator_loop" COMMAND iterator_loop)

add_executable(iterator_types iterator_types.cpp)
add_test(NAME "SL: iterator types" COMMAND iterator_types)

add_executable(slide slide.cpp)
add_test(NAME "SL: Slide" COMMAND slide)

add_executable(taylor taylor.cpp)
add_test(NAME "SL: Taylor" COMMAND taylor 100 0.5)

