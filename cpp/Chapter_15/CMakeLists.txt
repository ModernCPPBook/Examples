if(${WITH_HPX})
	add_hpx_executable(Listing_15_2 SOURCES Listing_15_2.cpp)
	target_include_directories(Listing_15_2 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_HPX})
	add_hpx_executable(Listing_15_7 SOURCES Listing_15_7.cpp)
	target_include_directories(Listing_15_7 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
if(${WITH_HPX})
	add_hpx_executable(Listing_15_5 SOURCES Listing_15_5.cpp)
	target_include_directories(Listing_15_5 PUBLIC ${CMAKE_SOURCE_DIR}/cpp/include/)

endif()
