#include <tint/tint.h>

#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>

#include <array>
#include <iostream>

extern "C"
{
    void initialize();
    void uninitialize();
    void glsl_to_wgsl(const void* bytes, int length, bool vertex);
    void spirv_to_wgsl(const void* bytes, int length);
    
    // Callback to JavaScript
    extern void return_string(const void* data, int length);
}

namespace
{
    const TBuiltInResource DefaultTBuiltInResource = {
        32,    // MaxLights
        6,     // MaxClipPlanes
        32,    // MaxTextureUnits
        32,    // MaxTextureCoords
        64,    // MaxVertexAttribs
        4096,  // MaxVertexUniformComponents
        64,    // MaxVaryingFloats
        32,    // MaxVertexTextureImageUnits
        80,    // MaxCombinedTextureImageUnits
        32,    // MaxTextureImageUnits
        4096,  // MaxFragmentUniformComponents
        32,    // MaxDrawBuffers
        128,   // MaxVertexUniformVectors
        8,     // MaxVaryingVectors
        16,    // MaxFragmentUniformVectors
        16,    // MaxVertexOutputVectors
        15,    // MaxFragmentInputVectors
        -8,    // MinProgramTexelOffset
        7,     // MaxProgramTexelOffset
        8,     // MaxClipDistances
        65535, // MaxComputeWorkGroupCountX
        65535, // MaxComputeWorkGroupCountY
        65535, // MaxComputeWorkGroupCountZ
        1024,  // MaxComputeWorkGroupSizeX
        1024,  // MaxComputeWorkGroupSizeY
        64,    // MaxComputeWorkGroupSizeZ
        1024,  // MaxComputeUniformComponents
        16,    // MaxComputeTextureImageUnits
        8,     // MaxComputeImageUniforms
        8,     // MaxComputeAtomicCounters
        1,     // MaxComputeAtomicCounterBuffers
        60,    // MaxVaryingComponents
        64,    // MaxVertexOutputComponents
        64,    // MaxGeometryInputComponents
        128,   // MaxGeometryOutputComponents
        128,   // MaxFragmentInputComponents
        8,     // MaxImageUnits
        8,     // MaxCombinedImageUnitsAndFragmentOutputs
        8,     // MaxCombinedShaderOutputResources
        0,     // MaxImageSamples
        0,     // MaxVertexImageUniforms
        0,     // MaxTessControlImageUniforms
        0,     // MaxTessEvaluationImageUniforms
        0,     // MaxGeometryImageUniforms
        8,     // MaxFragmentImageUniforms
        8,     // MaxCombinedImageUniforms
        16,    // MaxGeometryTextureImageUnits
        256,   // MaxGeometryOutputVertices
        1024,  // MaxGeometryTotalOutputComponents
        1024,  // MaxGeometryUniformComponents
        64,    // MaxGeometryVaryingComponents
        128,   // MaxTessControlInputComponents
        128,   // MaxTessControlOutputComponents
        16,    // MaxTessControlTextureImageUnits
        1024,  // MaxTessControlUniformComponents
        4096,  // MaxTessControlTotalOutputComponents
        128,   // MaxTessEvaluationInputComponents
        128,   // MaxTessEvaluationOutputComponents
        16,    // MaxTessEvaluationTextureImageUnits
        1024,  // MaxTessEvaluationUniformComponents
        120,   // MaxTessPatchComponents
        32,    // MaxPatchVertices
        64,    // MaxTessGenLevel
        16,    // MaxViewports
        0,     // MaxVertexAtomicCounters
        0,     // MaxTessControlAtomicCounters
        0,     // MaxTessEvaluationAtomicCounters
        0,     // MaxGeometryAtomicCounters
        8,     // MaxFragmentAtomicCounters
        8,     // MaxCombinedAtomicCounters
        1,     // MaxAtomicCounterBindings
        0,     // MaxVertexAtomicCounterBuffers
        0,     // MaxTessControlAtomicCounterBuffers
        0,     // MaxTessEvaluationAtomicCounterBuffers
        0,     // MaxGeometryAtomicCounterBuffers
        1,     // MaxFragmentAtomicCounterBuffers
        1,     // MaxCombinedAtomicCounterBuffers
        16384, // MaxAtomicCounterBufferSize
        4,     // MaxTransformFeedbackBuffers
        64,    // MaxTransformFeedbackInterleavedComponents
        8,     // MaxCullDistances
        8,     // MaxCombinedClipAndCullDistances
        4,     // MaxSamples
        256,   // maxMeshOutputVerticesNV
        512,   // maxMeshOutputPrimitivesNV
        32,    // maxMeshWorkGroupSizeX_NV
        1,     // maxMeshWorkGroupSizeY_NV
        1,     // maxMeshWorkGroupSizeZ_NV
        32,    // maxTaskWorkGroupSizeX_NV
        1,     // maxTaskWorkGroupSizeY_NV
        1,     // maxTaskWorkGroupSizeZ_NV
        4,     // maxMeshViewCountNV
        1,     // maxDualSourceDrawBuffersEXT

        // limits
        {
            1, // nonInductiveForLoops
            1, // whileLoops
            1, // doWhileLoops
            1, // generalUniformIndexing
            1, // generalAttributeMatrixVectorIndexing
            1, // generalVaryingIndexing
            1, // generalSamplerIndexing
            1, // generalVariableIndexing
            1, // generalConstantMatrixVectorIndexing
        },
    };
}

void initialize()
{
    glslang::InitializeProcess();
}

void uninitialize()
{
    glslang::FinalizeProcess();
}

void internal_spirv_to_wgsl(const std::vector<uint32_t>& spirv)
{
    tint::Program program{tint::reader::spirv::Parse(spirv)};

    for (const auto& message : program.Diagnostics())
    {
        // TODO: Handle the diagnostic messages.
    }
    
    tint::writer::wgsl::Options options{};
    auto result = tint::writer::wgsl::Generate(&program, options);
    
    return_string(result.wgsl.data(), result.wgsl.size());
}

void glsl_to_wgsl(const void* bytes, int length, bool vertex)
{
    std::vector<char> source{};
    source.resize(length);
    std::memcpy(source.data(), bytes, length);
    const EShLanguage stage{vertex ? EShLangVertex : EShLangFragment};
    
    glslang::TProgram program{};
    
    glslang::TShader shader{stage};
    const std::array<const char*, 1> sources{source.data()};
    shader.setStrings(sources.data(), static_cast<int>(sources.size()));
    
    shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientNone, 0);
    shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_1);
    shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);

    if (!shader.parse(&DefaultTBuiltInResource, 310, EProfile::EEsProfile, true, false, EShMsgDefault))
    {
        std::cout << shader.getInfoLog() << std::endl;
        throw std::runtime_error{shader.getInfoLog()};
    }

    program.addShader(&shader);

    glslang::SpvVersion spv{};
    spv.spv = 0x10000;
    shader.getIntermediate()->setSpv(spv);

    if (!program.link(EShMsgDefault))
    {
        throw std::runtime_error{program.getInfoLog()};
    }

    std::vector<uint32_t> spirv{};
    glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

    internal_spirv_to_wgsl(spirv);
}

void spirv_to_wgsl(const void* bytes, int length) {
    std::vector<uint32_t> spirv{};
    spirv.resize(length / sizeof(uint32_t));
    std::memcpy(spirv.data(), bytes, length);

    internal_spirv_to_wgsl(spirv);
}
