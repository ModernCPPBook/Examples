# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(${WITH_PAR_ALG})
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
        message(FATAL_ERROR "GCC version must be at least 9.0 for the parallel algorithms!")
    endif()

    add_executable(taylor_par taylor_par.cpp)
    target_link_libraries(taylor_par PUBLIC TBB::tbb)
    target_compile_options(taylor_par PRIVATE -std=c++1z)
    add_test(NAME "Parallel: Taylor parallel algorithms" COMMAND taylor_par 100 0.5)
endif()
endif()

add_executable(taylor_thread taylor_thread.cpp)
target_link_libraries(taylor_thread PRIVATE Threads::Threads)

add_test(NAME "Parallel: Taylor thread" COMMAND taylor_thread 100 0.5 3)

