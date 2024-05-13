if(${WITH_HPX})
	add_hpx_executable(Listing_14_7 SOURCES Listing_14_7.cpp)
	target_include_directories(Listing_14_7 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_MPI})
	add_executable(Listing_14_1 Listing_14_1.cpp)
endif()
if(${WITH_HPX})
	add_hpx_executable(Listing_14_5 SOURCES Listing_14_5.cpp)
	target_include_directories(Listing_14_5 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_HPX})
	add_hpx_executable(Listing_14_2 SOURCES Listing_14_2.cpp)
	target_include_directories(Listing_14_2 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
