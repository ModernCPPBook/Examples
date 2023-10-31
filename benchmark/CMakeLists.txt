# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.24)

project(Benchmark
    DESCRIPTION "Benchmarks used in the book"
    LANGUAGES CXX)

include(CTest)

add_executable(benchmark_containers benchmark_containers.cpp)
add_test(NAME "Benchmark_containers" COMMAND benchmark_containers 100)