# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_executable(serial serial.cpp)
add_test(NAME "Set: Serial Mandelbrot" COMMAND serial mandelbrot) 
add_test(NAME "Set: Serial Julia" COMMAND serial julia) 

add_executable(thread_parallel thread_parallel.cpp)
add_test(NAME "Set: Thread Mandelbrot" COMMAND thread_parallel 2) 

add_executable(future_parallel future_parallel.cpp)
add_test(NAME "Set: Future Mandelbrot" COMMAND future_parallel 2) 

if(${WITH_HPX})
    add_hpx_executable(algorithm_parallel SOURCES algorithm_parallel.cpp)
    add_test(NAME "Set: Parallel Algorithm Mandelbrot" COMMAND algorithm_parallel --hpx:threads=2)
    
    add_hpx_executable(future_parallel_hpx SOURCES future_parallel_hpx.cpp)
    add_test(NAME "Set: HPX Future Mandelbrot" COMMAND future_parallel_hpx)
endif()

if(${WITH_COROUTINES})
    add_hpx_executable(future_parallel_hpx_coroutine SOURCES future_parallel_hpx_coroutine.cpp)
    add_test(NAME "Set: HPX Future Coroutines Mandelbrot" COMMAND future_parallel_hpx_coroutine)
endif()

target_include_directories(serial PUBLIC "../util/")
target_include_directories(thread_parallel PUBLIC "../util/")
target_include_directories(future_parallel PUBLIC "../util/")

if(${WITH_HPX})
    target_include_directories(algorithm_parallel PUBLIC "../util/")
    target_include_directories(future_parallel_hpx PUBLIC "../util/")
endif()

if(${WITH_COROUTINES})
    target_include_directories(future_parallel_hpx_coroutine PUBLIC "../util/")
endif()

target_link_libraries(thread_parallel PRIVATE Threads::Threads)
target_link_libraries(future_parallel PRIVATE Threads::Threads)
