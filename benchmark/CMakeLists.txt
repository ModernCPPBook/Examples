# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.24)

project(Benchmark
    DESCRIPTION "Benchmarks used in the book"
    LANGUAGES CXX)

include(CTest)

SET(WITH_OPENMP OFF CACHE BOOL "Build OpenMP example")

if(NOT APPLE AND ${WITH_OPENMP})
    find_package(OpenMP REQUIRED)
endif()

add_executable(benchmark_containers benchmark_containers.cpp)
add_test(NAME "Benchmark_containers" COMMAND benchmark_containers 100)

if(NOT APPLE AND ${WITH_OPENMP})
   add_executable(openmp_parallel openmp_parallel.cpp)
   target_compile_options(openmp_parallel PUBLIC "${OpenMP_CXX_FLAGS}" )
   target_link_libraries(openmp_parallel PUBLIC OpenMP::OpenMP_CXX)
   target_include_directories(openmp_parallel PUBLIC "../util/")
   add_test(NAME "Set:_OpenMP_Mandelbrot" COMMAND openmp_parallel ) 
endif()