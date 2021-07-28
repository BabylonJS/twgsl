#include <tint/tint.h>
#include <iostream>

extern "C"
{
    void spirv_to_wgsl(void* bytes, int length);
}

void spirv_to_wgsl(void* bytes, int length) {
    std::vector<uint32_t> spirv{};
    spirv.resize(length / sizeof(uint32_t));
    std::memcpy(bytes, spirv.data(), length);
    tint::Program program{tint::reader::spirv::Parse(spirv)};
    tint::writer::wgsl::Options options{};
    auto result = tint::writer::wgsl::Generate(&program, options);
    std::cout << result.wgsl << std::endl;
}
