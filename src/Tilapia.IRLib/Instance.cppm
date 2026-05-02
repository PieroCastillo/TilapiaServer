module;

#include <cstdint>
#include <cstdlib>
#include <vector>

export module tilapia.irlib:instance;
import :ir;

export namespace Tilapia::IRLib
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

    inline uint32_t alignUp(uint32_t addr, uint32_t align)
    {
        return (addr + (align - 1)) & ~(align - 1);
    }

    void ConfigureInstance(binary* exe, Instance* instance, uint32_t arenaSize)
    {
        constexpr uint32_t align = 64;
        instance->ip = exe->header.entrypointOffset;
        instance->valueStack.resize(8192); // 8192 variables
        instance->callStack.reserve(1024); // depth limit
        // instance->memoryArena.resize(arenaSize);

        // ro | rw | bss | heap
        instance->roSize = alignUp(exe->readOnlyDataSize, align);
        instance->rwSize = alignUp(exe->readWriteDataSize, align);
        instance->bssSize = alignUp(exe->uninitializedDataSize, align);
        instance->heapSize = alignUp(arenaSize, align);

        // ro offset is 0
        instance->rwOffset = instance->roSize;
        instance->bssOffset = instance->rwSize;
        instance->heapOffset = instance->bssSize;

        auto fullMemorySize = instance->roSize + instance->rwSize + instance->bssSize + instance->heapSize;
        // init zero-filled memory
        instance->memoryArena.resize(fullMemorySize, 0);

        // copy
        memcpy((void*)((uint8_t*)instance->memoryArena.data() + 0), exe->readOnlyDataPool.data(), exe->readOnlyDataSize);
        memcpy((void*)((uint8_t*)instance->memoryArena.data() + instance->rwOffset), exe->readWriteDataPool.data(), exe->readWriteDataSize);
    }
};