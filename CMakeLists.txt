# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project(Examples
    DESCRIPTION "Book examples"
    LANGUAGES CXX)

cmake_minimum_required(VERSION 3.19)

SET(WITH_PAR_ALG OFF CACHE BOOL "Build parallel algorithm example")
SET(WITH_HPX OFF CACHE BOOL "Build HPX example")

include(CTest)
include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-std=c++20 HAVE_FLAG_STD_CXX20)

if(${WITH_PAR_ALG})
    find_package(TBB REQUIRED)
    add_subdirectory(parallel_algorithm)
endif()

if(${WITH_HPX})
    find_package(HPX REQUIRED)
    add_subdirectory(hpx)
endif()

if(${HAVE_FLAG_STD_CXX20})

    set(CMAKE_CXX_STANDARD 20)

else()

    check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
    
    if(${HAVE_FLAG_STD_CXX17})

        set(CMAKE_CXX_STANDARD 17)
    else()
         message( FATAL_ERROR "Your compiler needs to support at least CXX 17")
    endif()
endif()

add_subdirectory(appendix)
add_subdirectory(sl)
add_subdirectory(set)
