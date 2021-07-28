set(SOURCES 
    "Source/main.cpp")

add_executable(twgsl ${SOURCES})
target_link_libraries(twgsl PRIVATE libtint)
target_link_options(twgsl PRIVATE -s EXPORTED_FUNCTIONS=["_spirv_to_wgsl","_free"])
