module;

#include <array>
#include <cstdint>
#include <expected>
#include <span>
#include <string>

export module tilapia.irlib:assemblyLoader;
import :ir;
import :instance;

export namespace Tilapia::IRLib
{
    enum class ValidationError
    {
        BadMagic,
        BadMajor,
        BadMinor,
        OffsetsNotStrictlyIncreasing,
        BadChecksum
    };

    enum class BinaryValidationError
    {
        CapabilityNotSupported,
        DynamicLibraryNotPresent,
    };

    std::string extractString(std::span<const uint8_t> rawBytes, size_t offset, size_t count)
    {
        auto ptr = reinterpret_cast<char const*>(rawBytes.data() + offset);
        return std::string(ptr, count);
    }

    auto validateDesc(const binaryDesc& desc) -> std::expected<void, ValidationError>
    {
        constexpr uint32_t expectedMagic = 0x74694952; // "tiIR"
        constexpr uint16_t expectedMajor = 1;
        constexpr uint16_t expectedMinor = 0;

        if (desc.magic != expectedMagic)
            return std::unexpected(ValidationError::BadMagic);

        if (desc.versionMajor != expectedMajor)
            return std::unexpected(ValidationError::BadMajor);

        if (desc.versionMinor != expectedMinor)
            return std::unexpected(ValidationError::BadMinor);


        constexpr auto strictlyIncreasing = [](auto const& vals)
            {
                for (size_t i = 1; i < vals.size(); ++i)
                    if (vals[i] <= vals[i - 1])
                        return false;
                return true;
            };

        std::array<uint32_t, 13> offsets
        {
            desc.executableNameOffset,
            desc.capabilitiesOffset,
            desc.typesOffset,
            desc.typesPoolOffset,
            desc.symbolsOffset,
            desc.dynamicLibsOffset,
            desc.entrypointsOffset,
            desc.functionsOffset,
            desc.roDataOffset,
            desc.roDataPoolOffset,
            desc.rwDataOffset,
            desc.rwDataPoolOffset,
            desc.instructionsOffset,
        };

        if (!strictlyIncreasing(offsets))
            return std::unexpected(ValidationError::OffsetsNotStrictlyIncreasing);

        return {};
    }

    auto loadDesc(std::span<const uint8_t> asmBytes, bool validate = true) -> std::expected<binaryDesc, ValidationError>
    {
        binaryDesc desc = {};
        // read first 128 bytes
        memcpy(&desc, asmBytes.data(), sizeof(binaryDesc));

        // validation
        if (!validate)
        {
            return desc;
        }

        auto v = validateDesc(desc);
        if (!v)
            return std::unexpected(v.error());

        return desc;
    }

    auto loadBin(std::span<const uint8_t> asmBytes, const binaryDesc& desc) -> std::expected<binary, BinaryValidationError>
    {
        binary exec = {};

        exec.header = {
            .magic = desc.magic,
            .versionMajor = desc.versionMajor,
            .versionMinor = desc.versionMinor,
            .flags = desc.flags,
            .entrypointOffset = desc.mainEntrypointIndex,
        };

        exec.capabilities.resize(desc.capabilitiesCount);
        memcpy(exec.capabilities.data(), asmBytes.data() + desc.capabilitiesOffset, desc.capabilitiesCount * sizeof(capabilityEntry));

        exec.types.resize(desc.typesCount);
        exec.typesPool.resize(desc.typesPoolSize);
        memcpy(exec.types.data(), asmBytes.data() + desc.typesOffset, desc.typesCount * sizeof(typeEntry));
        memcpy(exec.typesPool.data(), asmBytes.data() + desc.typesPoolOffset, desc.typesPoolSize);

        exec.symbols.resize(desc.symbolsCount);
        exec.dynamicLibs.resize(desc.dynamicLibsCount);
        exec.entrypoints.resize(desc.entrypointsCount);
        exec.functions.resize(desc.functionsCount);
        memcpy(exec.symbols.data(), asmBytes.data() + desc.symbolsOffset, desc.symbolsCount * sizeof(symbolEntry));
        memcpy(exec.dynamicLibs.data(), asmBytes.data() + desc.dynamicLibsOffset, desc.dynamicLibsCount * sizeof(dynamicLibRef));
        memcpy(exec.entrypoints.data(), asmBytes.data() + desc.entrypointsOffset, desc.entrypointsCount * sizeof(entrypoint));
        memcpy(exec.functions.data(), asmBytes.data() + desc.functionsOffset, desc.functionsCount * sizeof(functionEntry));

        exec.readOnlyDataSize = desc.roDataCount;
        exec.readWriteDataSize = desc.rwDataCount;
        exec.uninitializedDataSize = desc.uninitializedDataSize;

        exec.readOnlyData.resize(desc.roDataCount);
        exec.readOnlyDataPool.resize(desc.roDataPoolSize);
        memcpy(exec.readOnlyData.data(), asmBytes.data() + desc.roDataOffset, desc.roDataCount * sizeof(dataEntry));
        memcpy(exec.readOnlyDataPool.data(), asmBytes.data() + desc.roDataPoolOffset, desc.roDataPoolSize);

        exec.readWriteData.resize(desc.rwDataCount);
        exec.readWriteDataPool.resize(desc.rwDataPoolSize);
        memcpy(exec.readWriteData.data(), asmBytes.data() + desc.rwDataOffset, desc.rwDataCount * sizeof(dataEntry));
        memcpy(exec.readWriteDataPool.data(), asmBytes.data() + desc.rwDataPoolOffset, desc.rwDataPoolSize);

        exec.instructions.resize(desc.instructionsCount);
        memcpy(exec.instructions.data(), asmBytes.data() + desc.instructionsOffset, desc.instructionsCount * sizeof(instruction));

        exec.header.executableName = extractString(asmBytes, desc.executableNameOffset, desc.executableNameCharCount);

        // TODO: file validation lies here

        return exec;
    }
};