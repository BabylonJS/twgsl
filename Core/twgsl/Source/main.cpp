#include <tint/tint.h>

#include <array>
#include <iostream>

extern "C"
{
    void test();
    void spirv_to_wgsl(const void* bytes, int length);
    
    // Callback to JavaScript
    extern void return_string(const void* data, int length);
}

namespace
{
    constexpr std::array<uint32_t, 132> DEBUG_SPIRV_VALUES{
        119734787,
        65536,
        524296,
        18,
        0,
        131089,
        1,
        393227,
        1,
        1280527431,
        1685353262,
        808793134,
        0,
        196622,
        0,
        1,
        393231,
        0,
        4,
        1852399981,
        0,
        10,
        196611,
        1,
        310,
        262149,
        4,
        1852399981,
        0,
        393221,
        8,
        1348430951,
        1700164197,
        2019914866,
        0,
        393222,
        8,
        0,
        1348430951,
        1953067887,
        7237481,
        458758,
        8,
        1,
        1348430951,
        1953393007,
        1702521171,
        0,
        196613,
        10,
        0,
        327752,
        8,
        0,
        11,
        0,
        327752,
        8,
        1,
        11,
        1,
        196679,
        8,
        2,
        131091,
        2,
        196641,
        3,
        2,
        196630,
        6,
        32,
        262167,
        7,
        6,
        4,
        262174,
        8,
        7,
        6,
        262176,
        9,
        3,
        8,
        262203,
        9,
        10,
        3,
        262165,
        11,
        32,
        1,
        262187,
        11,
        12,
        0,
        262187,
        6,
        13,
        0,
        262187,
        6,
        14,
        1065353216,
        458796,
        7,
        15,
        13,
        13,
        13,
        14,
        262176,
        16,
        3,
        7,
        327734,
        2,
        4,
        0,
        3,
        131320,
        5,
        327745,
        16,
        17,
        10,
        12,
        196670,
        17,
        15,
        65789,
        65592
    };
}

void test()
{
    std::cout << "Starting..." << std::endl;
    spirv_to_wgsl(DEBUG_SPIRV_VALUES.data(), DEBUG_SPIRV_VALUES.size() * sizeof(uint32_t));
    std::cout << "Stopping." << std::endl;
}

void spirv_to_wgsl(const void* bytes, int length) {
    std::vector<uint32_t> spirv{};
    spirv.resize(length / sizeof(uint32_t));
    std::memcpy(spirv.data(), bytes, length);

    tint::Program program{tint::spirv::reader::Parse(spirv)};

    for (const auto& message : program.Diagnostics())
    {
        std::cout << message.message << std::endl << std::endl;
    }
    
    tint::wgsl::writer::Options options{};
    auto result = tint::wgsl::writer::Generate(&program, options);

    return_string(result.wgsl.data(), result.wgsl.size());
}
