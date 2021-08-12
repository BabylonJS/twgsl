cmake_minimum_required(VERSION 3.16)

project(twgsl)

add_subdirectory(Dependencies)

target_compile_options(SPIRV-Tools-static PRIVATE -Oz)
target_compile_options(SPIRV-Tools-opt PRIVATE -Oz)
target_compile_options(libtint PRIVATE -Oz)

add_subdirectory(Core)
