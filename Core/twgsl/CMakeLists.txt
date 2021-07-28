set(SOURCES 
    "Source/main.cpp")

add_library(twgsl ${SOURCES})
target_link_libraries(twgsl PRIVATE libtint)
