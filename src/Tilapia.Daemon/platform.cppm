/*
Created by @PieroCastillo on 2026-05-03
*/
module;

#include <cstdint>
#include <string>
#include <string_view>
#include <tuple>

export module tilapia.platform;

export namespace Tilapia::Daemon
{
    void ensureSingle();

    struct SharedMemory
    {
        uint8_t* data{};
        uint32_t size{};
        uint64_t handle{};
        SharedMemory() = default;
        SharedMemory(uint8_t* p, uint32_t s, uint64_t h) : data(p), size(s), handle(h) {}
        ~SharedMemory();
    };

    auto sharedAlloc(uint32_t size) -> SharedMemory;
    auto sharedOpen(uint64_t inheritedHandle) -> SharedMemory;
}