# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project(Examples
    DESCRIPTION "Book examples"
    LANGUAGES CXX)

cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(util)
add_subdirectory(appendix)
