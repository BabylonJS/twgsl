# ---------- tint ----------
option(TINT_BUILD_SPV_READER "Build the SPIR-V input reader" ON)
option(TINT_BUILD_WGSL_READER "Build the WGSL input reader" OFF)
option(TINT_BUILD_HLSL_WRITER "Build the HLSL output writer" OFF)
option(TINT_BUILD_MSL_WRITER "Build the MSL output writer" OFF)
option(TINT_BUILD_SPV_WRITER "Build the SPIR-V output writer" OFF)
option(TINT_BUILD_WGSL_WRITER "Build the WGSL output writer" ON)
add_subdirectory(tint EXCLUDE_FROM_ALL)


# ---------- glslang ----------
set(SKIP_GLSLANG_INSTALL OFF CACHE BOOL "Skip installation")
set(ENABLE_SPVREMAPPER OFF CACHE BOOL "Enables building of SPVRemapper")
set(ENABLE_GLSLANG_BINARIES OFF CACHE BOOL "Builds glslangValidator and spirv-remap")
set(ENABLE_HLSL OFF CACHE BOOL "Enables HLSL input support")
set(ENABLE_OPT OFF CACHE BOOL "Enables spirv-opt capability if present")
set(BUILD_EXTERNAL OFF CACHE BOOL "Build external dependencies in /External")
add_subdirectory(glslang EXCLUDE_FROM_ALL)
