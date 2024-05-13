if(${WITH_HPX})
	add_hpx_executable(Listing_11_1 SOURCES Listing_11_1.cpp)
	target_include_directories(Listing_11_1 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_HPX})
	add_hpx_executable(Listing_11_2 SOURCES Listing_11_2.cpp)
	target_include_directories(Listing_11_2 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_HPX})
	add_hpx_executable(Listing_11_3 SOURCES Listing_11_3.cpp)
	target_include_directories(Listing_11_3 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
