# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.17)

project(Examples
DESCRIPTION "Book examples"
LANGUAGES CXX)
SET(WITH_MPI OFF CACHE BOOL "Build MPI example")
SET(WITH_HPX OFF CACHE BOOL "Build HPX examples")
include(CTest)
add_subdirectory(cpp)
include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-std=c++20 HAVE_FLAG_STD_CXX20)

if(${WITH_MPI})
    find_package(MPI REQUIRED COMPONENTS CXX )
endif()