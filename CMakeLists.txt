CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

project( lsd )

add_definitions( -std=c++0x )

#find_package( Boost REQUIRED )
#include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ./ )

#add_subdirectory( src )
add_subdirectory(thirdparty)
add_subdirectory( test )
