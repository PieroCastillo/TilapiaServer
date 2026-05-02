module;

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <expected>
#include <ranges>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

export module tilapia.irlib:assemblyWritter;
import :ir;
import :instance;

export namespace Tilapia::IRLib
{
    template<class T>
    concept ContiguousContainer =
        requires(const T & t)
    {
        typename T::value_type;
        { t.data() };
        { t.size() } -> std::convertible_to<size_t>;
    }
    && std::is_trivially_copyable_v<typename T::value_type>;

    template<class T>
    concept ByteSpan =
        std::same_as<T, std::span<uint8_t>> ||
        std::same_as<T, std::span<const uint8_t>>;

    template<class T>
    void append(std::vector<uint8_t>& buffer, const T& value, uint32_t alignment, uint32_t lastOffset, uint32_t& offset)
    {
        const uint8_t* src = nullptr;
        size_t bytes = 0;

        if constexpr (std::is_trivially_copyable_v<T> && !ContiguousContainer<T>)
        {
            src = reinterpret_cast<const uint8_t*>(&value);
            bytes = sizeof(T);
        }
        else if constexpr (ContiguousContainer<T>)
        {
            using E = typename T::value_type;

            src = reinterpret_cast<const uint8_t*>(value.data());
            bytes = value.size() * sizeof(E);
        }
        else if constexpr (ByteSpan<T>)
        {
            src = value.data();
            bytes = value.size();
        }
        else
        {
            static_assert([] { return false; }(), "append(): unsupported type");
        }

        offset = alignUp(lastOffset + 1, alignment);

        const size_t required = offset + bytes;
        if (buffer.size() < required)
            buffer.resize(required);

        if (bytes)
            std::memcpy(buffer.data() + offset, src, bytes);
    }

    auto makeBinary(const binary& bin) -> std::vector<uint8_t>
    {
        constexpr uint32_t alignment = 64;
        std::vector<uint8_t> asmBytes;
        binaryDesc desc = {};

        desc.magic = 0x74694952; // 0x74694952 "tiIR"
        desc.versionMajor = 1;
        desc.versionMinor = 0;
        desc.flags = 0x0000000;
        desc.binaryChecksum = 0x00000000;
        desc.mainEntrypointIndex = 0;
        desc.executableNameCharCount = bin.header.executableName.size(); // ascii characters

        desc.capabilitiesCount = bin.capabilities.size();
        desc.typesCount = bin.types.size();
        desc.typesPoolSize = bin.typesPool.size();
        desc.symbolsCount = bin.symbols.size();
        desc.dynamicLibsCount = bin.dynamicLibs.size();
        desc.entrypointsCount = bin.entrypoints.size();
        desc.functionsCount = bin.functions.size();

        desc.roDataCount = bin.readOnlyData.size();
        desc.roDataPoolSize = bin.readOnlyDataPool.size();
        desc.rwDataCount = bin.readWriteData.size();
        desc.rwDataPoolSize = bin.readWriteDataPool.size();
        desc.uninitializedDataSize = bin.uninitializedDataSize;

        desc.instructionsCount = bin.instructions.size();

        // yeah, i'm gonna copy an incomplete copy of binary desc
        // nvm, i'm going to copy the corrected version after 
        uint32_t dummyOffset = 0;
        append(asmBytes, desc, alignment, 0, dummyOffset);
        append(asmBytes, bin.header.executableName, alignment, dummyOffset, desc.executableNameOffset);
        append(asmBytes, bin.capabilities, alignment, desc.executableNameOffset, desc.capabilitiesOffset);
        append(asmBytes, bin.types, alignment, desc.capabilitiesOffset, desc.typesOffset);
        append(asmBytes, bin.typesPool, alignment, desc.typesOffset, desc.typesPoolOffset);
        append(asmBytes, bin.symbols, alignment, desc.typesPoolOffset, desc.symbolsOffset);
        append(asmBytes, bin.dynamicLibs, alignment, desc.symbolsOffset, desc.dynamicLibsOffset);
        append(asmBytes, bin.entrypoints, alignment, desc.dynamicLibsOffset, desc.entrypointsOffset);
        append(asmBytes, bin.functions, alignment, desc.entrypointsOffset, desc.functionsOffset);
        append(asmBytes, bin.readOnlyData, alignment, desc.functionsOffset, desc.roDataOffset);
        append(asmBytes, bin.readOnlyDataPool, alignment, desc.roDataOffset, desc.roDataPoolOffset);
        append(asmBytes, bin.readWriteData, alignment, desc.roDataPoolOffset, desc.rwDataOffset);
        append(asmBytes, bin.readWriteDataPool, alignment, desc.rwDataOffset, desc.rwDataPoolOffset);
        append(asmBytes, bin.instructions, alignment, desc.rwDataPoolOffset, desc.instructionsOffset);

        // full copy of binaryDesc
        memcpy(asmBytes.data(), &desc, sizeof(binaryDesc));
    }
}