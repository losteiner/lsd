CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

project( StringPainter )

add_definitions( -std=c++0x )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_subdirectory( src )

