/*
Created by @PieroCastillo on 2026-04-16
*/
#ifndef TILAPIA_RUNTIME_INSTANCE_HPP
#define TILAPIA_RUNTIME_INSTANCE_HPP

#include <cstdint>
#include <vector>

#include "IR.hpp"

namespace TilapiaServer::Runtime
{
    struct CallFrame
    {
        uint32_t returnIP;
        uint32_t returnBP;
    };

    struct Instance
    {
        std::vector<uint64_t> valueStack;
        std::vector<CallFrame> callStack;
        std::vector<uint8_t> memoryArena; // ro | rw | bss | heap
        uint32_t rwOffset, bssOffset, heapOffset;
        uint32_t roSize, rwSize, bssSize, heapSize;
        uint32_t arenaOffset = 0;

        uint32_t ip = 0; // instruction ptr
        uint32_t bp = 0; // base ptr
        uint32_t sp = 0; // stack ptr

        bool isRunning = false;
        int32_t exitCode = 0;
    };

    void ConfigureInstance(IR::binary* exe, Instance* instance, uint32_t arenaSize);
};
#endif // TILAPIA_RUNTIME_INSTANCE_HPP