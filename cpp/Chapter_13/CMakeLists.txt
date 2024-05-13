if(${WITH_MPI})
	# add mpi compile
endif()
if(${WITH_MPI})
	# add mpi compile
target_include_directories(Listing_13_1 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_MPI})
	# add mpi compile
endif()
add_executable(Listing_13_4 Listing_13_4.cpp)
target_include_directories(Listing_13_4 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

