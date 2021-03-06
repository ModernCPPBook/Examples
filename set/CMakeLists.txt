# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_executable(serial serial.cpp)
add_test(NAME "Set: Serial Mandelbrot" COMMAND serial mandelbrot) 
add_test(NAME "Set: Serial Julia" COMMAND serial julia) 

add_executable(thread_parallel thread_parallel.cpp)
add_test(NAME "Set: Thread Mandelbrot" COMMAND thread_parallel mandelbrot) 

add_executable(future_parallel future_parallel.cpp)
add_test(NAME "Set: Future Mandelbrot" COMMAND future_parallel mandelbrot) 

target_include_directories(serial PUBLIC "../util/")
target_include_directories(thread_parallel PUBLIC "../util/")
target_include_directories(future_parallel PUBLIC "../util/")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(thread_parallel PRIVATE Threads::Threads)
target_link_libraries(future_parallel PRIVATE Threads::Threads)
