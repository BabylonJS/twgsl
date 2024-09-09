cmake_minimum_required(VERSION 3.16)

project(twgsl)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Dependencies)

#target_compile_options(SPIRV-Tools-static PRIVATE -Oz)
#target_compile_options(SPIRV-Tools-opt PRIVATE -Oz)
target_compile_options(tint_api PRIVATE -Oz)
target_compile_options(tint_utils_system PRIVATE "-Wno-disabled-macro-expansion")

add_subdirectory(Core)
