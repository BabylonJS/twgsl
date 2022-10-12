cmake_minimum_required(VERSION 3.16)

cmake_policy(SET CMP0063 NEW)

project(twgsl)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Dependencies)

target_compile_options(SPIRV-Tools-static PRIVATE -Oz)
target_compile_options(SPIRV-Tools-opt PRIVATE -Oz)
target_compile_options(libtint PRIVATE -Oz)

add_subdirectory(Core)
