# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_executable(templates templates.cpp)
add_test(NAME "Appendix:_Template" COMMAND templates)

add_executable(lambda lambda.cpp)
add_test(NAME "Appendix:_Lambda" COMMAND lambda)

add_executable(move move.cpp)
add_test(NAME "Appendix:_Move" COMMAND move)

add_executable(ranges_pure ranges_pure.cpp)
add_test(NAME "Appendix:_Ranges pure" COMMAND ranges_pure)

add_executable(unique_pointer unique_pointer.cpp)
add_test(NAME "Appendix:_Unique_pointer" COMMAND unique_pointer)

add_executable(shared_pointer shared_pointer.cpp)
add_test(NAME "Appendix:_Shared_pointer" COMMAND shared_pointer)

add_executable(new new.cpp)
add_test(NAME "Appendix:_New" COMMAND new)

if(${HAVE_FLAG_STD_CXX20} AND NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
add_executable(ranges ranges.cpp)
add_test(NAME "Appendix:_Ranges" COMMAND ranges)
endif()
