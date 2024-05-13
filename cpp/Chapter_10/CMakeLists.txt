if(${WITH_HPX})
	add_hpx_executable(Listing_10_4 SOURCES Listing_10_4.cpp)
	target_include_directories(Listing_10_4 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
