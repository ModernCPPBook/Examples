# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.17)

project(Examples
DESCRIPTION "Book examples"
LANGUAGES CXX)
SET(WITH_MPI OFF CACHE BOOL "Build MPI example")
SET(WITH_HPX_SIMD OFF CACHE BOOL "Build HPX SIMD example")
SET(WITH_HPX_COROUTINE OFF CACHE BOOL "Build HPX COROUTINE example")
include(CTest)
include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-std=c++20 HAVE_FLAG_STD_CXX20)

if(${HAVE_FLAG_STD_CXX20})
    set(CMAKE_CXX_STANDARD 20)
else()
    set(CMAKE_CXX_STANDARD 17)
endif()
if(${WITH_MPI})
    find_package(MPI REQUIRED COMPONENTS CXX )
endif()
if(${WITH_HPX})
    find_package(HPX REQUIRED)
endif()

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
add_subdirectory(cpp)
