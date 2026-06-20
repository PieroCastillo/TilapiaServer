/*
Created by @PieroCastillo on 2026-05-03
*/
module;

#include <cstdint>
#include <string>
#include <string_view>
#include <tuple>

export module tilapia.platform:sharedMemory;

export namespace Tilapia::Platform
{
    struct SharedMemory
    {
        uint8_t* data{};
        uint32_t size{};
        uint64_t handle{};
        const bool isOwner;
        SharedMemory() : isOwner(false) {};
        explicit SharedMemory(uint8_t* p, uint32_t s, uint64_t h, bool io) : data(p), size(s), handle(h), isOwner(io) {}
        ~SharedMemory();
    };

    auto sharedAlloc(uint32_t size) -> SharedMemory;
    auto sharedOpen(uint64_t inheritedHandle, uint32_t size) -> SharedMemory;
}