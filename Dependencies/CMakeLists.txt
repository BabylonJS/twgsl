option(TINT_BUILD_SPV_READER "Build the SPIR-V input reader" ON)
option(TINT_BUILD_WGSL_READER "Build the WGSL input reader" OFF)
option(TINT_BUILD_HLSL_WRITER "Build the HLSL output writer" OFF)
option(TINT_BUILD_MSL_WRITER "Build the MSL output writer" OFF)
option(TINT_BUILD_SPV_WRITER "Build the SPIR-V output writer" OFF)
option(TINT_BUILD_WGSL_WRITER "Build the WGSL output writer" ON)
add_subdirectory(tint EXCLUDE_FROM_ALL)

# Patch compile option
function(tint_patch_compile_options TARGET)
  set(COMMON_CLANG_OPTIONS -Wno-unsafe-buffer-usage)
  target_compile_options(${TARGET} PRIVATE ${COMMON_CLANG_OPTIONS})
endfunction()

tint_patch_compile_options(tint_diagnostic_utils)
tint_patch_compile_options(tint_utils_io)
tint_patch_compile_options(tint_val)
tint_patch_compile_options(libtint)
tint_patch_compile_options(tint)
