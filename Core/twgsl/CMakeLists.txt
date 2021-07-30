set(SOURCES 
    "Source/main.cpp")

add_executable(twgsl ${SOURCES})
target_link_libraries(twgsl
    PRIVATE libtint
    PRIVATE glslang
    PRIVATE SPIRV)
target_link_options(twgsl PRIVATE "SHELL:-s EXPORTED_FUNCTIONS=[\"_initialize\",\"_uninitialize\",\"_spirv_to_wgsl\",\"_glsl_to_wgsl\",\"_malloc\",\"_free\"]")
target_link_options(twgsl PRIVATE "SHELL:-s EXPORTED_RUNTIME_METHODS=[\"stringToUTF8\"]")
target_link_options(twgsl PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
target_link_options(twgsl PRIVATE "SHELL:--js-library ${CMAKE_CURRENT_SOURCE_DIR}/Source/callbacks.js")
target_link_options(twgsl PRIVATE "SHELL:-O2")
#target_link_options(twgsl PRIVATE "SHELL:-s NO_DISABLE_EXCEPTION_CATCHING")
