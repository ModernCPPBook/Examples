if("${HAVE_FLAG_STD_CXX20}" AND NOT ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"))
add_executable(Listing_3_6 Listing_3_6.cpp)
SET_PROPERTY(TARGET Listing_3_6 PROPERTY CXX_STANDARD 20)
endif()
