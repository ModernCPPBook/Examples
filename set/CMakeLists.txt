# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(NOT APPLE AND ${WITH_OPENMP})
   add_executable(openmp_parallel openmp_parallel.cpp)
   target_compile_options(openmp_parallel PUBLIC "${OpenMP_CXX_FLAGS}" )
   target_link_libraries(openmp_parallel PUBLIC OpenMP::OpenMP_CXX)
   target_include_directories(openmp_parallel PUBLIC "../util/")
   add_test(NAME "Set:_OpenMP_Mandelbrot" COMMAND serial) 
endif()

add_executable(serial serial.cpp)
add_test(NAME "Set:_Serial_Mandelbrot" COMMAND serial) 
add_test(NAME "Set:_Serial_Julia" COMMAND serial julia) 

add_executable(thread_parallel thread_parallel.cpp)
add_test(NAME "Set:_Thread_Mandelbrot" COMMAND thread_parallel 2) 

add_executable(future_parallel future_parallel.cpp)
add_test(NAME "Set:_Future_Mandelbrot" COMMAND future_parallel 2) 

if(${WITH_HPX})
    add_hpx_executable(numa_parallel SOURCES numa_parallel.cpp)
    add_hpx_executable(algorithm_parallel SOURCES algorithm_parallel.cpp)
    add_test(NAME "Set:_Parallel_Algorithm_Mandelbrot" COMMAND algorithm_parallel --hpx:threads=2)
    
    add_hpx_executable(future_parallel_hpx SOURCES future_parallel_hpx.cpp)
    add_test(NAME "Set:_HPX_Future_Mandelbrot" COMMAND future_parallel_hpx)
endif()

if(${WITH_COROUTINES})
    add_hpx_executable(future_parallel_hpx_coroutine SOURCES future_parallel_hpx_coroutine.cpp)
    add_test(NAME "Set:_HPX_Future_Coroutines_Mandelbrot" COMMAND future_parallel_hpx_coroutine)
endif()

target_include_directories(serial PUBLIC "../util/")
target_include_directories(thread_parallel PUBLIC "../util/")
target_include_directories(future_parallel PUBLIC "../util/")

if(${WITH_MPI})
   add_executable(mpi mpi.cpp)
   target_link_libraries(mpi PUBLIC MPI::MPI_CXX)
   target_include_directories(mpi PUBLIC "../util/")
   add_test(NAME "Set:_MPI" COMMAND mpirun -np 1 ./mpi)
   if(${WITH_OPENMP})
   add_executable(mpi_openmp mpi.cpp)
   target_compile_options(mpi_openmp PUBLIC "${OpenMP_CXX_FLAGS}" )
   target_link_libraries(mpi_openmp PUBLIC MPI::MPI_CXX)
   target_link_libraries(mpi_openmp PUBLIC OpenMP::OpenMP_CXX)
   target_include_directories(mpi_openmp PUBLIC "../util/")
   endif()
endif()

if(${WITH_HPX})
    target_include_directories(algorithm_parallel PUBLIC "../util/")
    target_include_directories(numa_parallel PUBLIC "../util/")
    target_include_directories(future_parallel_hpx PUBLIC "../util/")
endif()

if(${WITH_COROUTINES})
    target_include_directories(future_parallel_hpx_coroutine PUBLIC "../util/")
endif()

target_link_libraries(thread_parallel PRIVATE Threads::Threads)
target_link_libraries(future_parallel PRIVATE Threads::Threads)
