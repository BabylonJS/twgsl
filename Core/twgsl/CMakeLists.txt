set(SOURCES 
    "Source/main.cpp")

add_executable(twgsl ${SOURCES})
target_compile_options(twgsl PRIVATE -Oz)
target_compile_options(twgsl PRIVATE -s TOTAL_MEMORY=33554432)
target_link_libraries(twgsl PRIVATE libtint)
target_link_options(twgsl PRIVATE -s EXPORTED_FUNCTIONS=["_test","_spirv_to_wgsl","_free"])
target_link_options(twgsl PRIVATE -s --js-library ${CMAKE_CURRENT_SOURCE_DIR}/Source/callbacks.js)
target_link_options(twgsl PRIVATE -Oz)
target_link_options(twgsl PRIVATE -flto)
