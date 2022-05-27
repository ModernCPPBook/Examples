# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_executable(template templates.cpp)
add_executable(lambda lambda.cpp)
add_executable(move move.cpp)
add_executable(ranges_pure ranges_pure.cpp)

if(HAVE_FLAG_STD_CXX20)
add_executable(ranges ranges.cpp)
endif()
