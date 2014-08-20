
add_executable( StringPainter
    # Add source files here
    StringPainter.cpp
)

target_link_libraries( StringPainter
    # Add libraries here
    ${OpenCV_LIBS}
)
