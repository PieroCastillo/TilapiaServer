module;

#include <cstdint>
#include <tuple>

export module tilapia.irlib:utils;
import :ir;

export namespace Tilapia::IRLib
{
    constexpr uint32_t alignUp(uint32_t addr, uint32_t align)
    {
        return (addr + (align - 1)) & ~(align - 1);
    }

    constexpr auto unpackFatPtr(uint64_t fatPtr) -> std::tuple<uint32_t, uint32_t>
    {
        uint32_t size = fatPtr >> 32;
        uint32_t address = fatPtr & 0xFFFFFFFFu;

        return { size, address };
    }
}