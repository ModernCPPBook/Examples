if(${WITH_MPI})
	add_executable(Listing_13_6 Listing_13_6.cpp)
	target_include_directories(Listing_13_6 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
add_executable(Listing_13_4 Listing_13_4.cpp)
target_include_directories(Listing_13_4 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

if(${WITH_MPI})
	add_executable(Listing_13_1 Listing_13_1.cpp)
	target_include_directories(Listing_13_1 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_MPI})
	add_executable(Listing_13_3 Listing_13_3.cpp)
	target_include_directories(Listing_13_3 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
