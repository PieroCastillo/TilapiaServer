module;

#include <cstdint>
#include <tuple>

export module tilapia.irlib:utils;
import :ir;

export namespace Tilapia::IRLib
{
    constexpr auto unpackFatPtr(uint64_t fatPtr) -> std::tuple<uint32_t, uint32_t>
    {
        uint32_t size = fatPtr >> 32;
        uint32_t address = fatPtr & 0xFFFFFFFFu;

        return { size, address };
    }
}