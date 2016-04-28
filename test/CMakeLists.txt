message( STATUS ${CMAKE_SOURCE_DIR} )

################################
# GTest
################################
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories( ${CMAKE_SOURCE_DIR}/lsd )
include_directories( ${CMAKE_SOURCE_DIR}/src )

add_executable( AllTests
    AllTests.cpp
    generic/unittest_lsd_bitfieldcounter.cpp
    generic/unittest_lsd_ringbuffer.cpp
)

target_link_libraries( AllTests
    #Foo
    gtest
    #${Boost_LIBRARIES}
)
