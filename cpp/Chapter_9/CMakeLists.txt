if(${WITH_HPX})
	add_hpx_executable(Listing_9_8 SOURCES Listing_9_8.cpp)
	target_include_directories(Listing_9_8 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
