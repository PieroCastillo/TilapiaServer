#include <cstdint>
#include <vector>

#include "Instance.hpp"

using namespace TilapiaServer::Runtime;

inline uint32_t alignUp(uint32_t addr, uint32_t align)
{
    return (addr + (align - 1)) & ~(align - 1);
}

void TilapiaServer::Runtime::ConfigureInstance(IR::binary* exe, Instance* instance, uint32_t arenaSize)
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
    instance->rwOffset = instance->roSize + 1;
    instance->bssOffset = instance->rwSize + 1;
    instance->heapOffset = instance->bssSize + 1;

    auto fullMemorySize = instance->roSize + instance->rwSize + instance->bssSize + instance->heapSize;
    // init zero-filled memory
    instance->memoryArena.resize(fullMemorySize, 0);

    // copy
    memcpy((void*)((uint8_t*)instance->memoryArena.data() + 0), exe->readOnlyDataPool.data(), exe->readOnlyDataSize);
    memcpy((void*)((uint8_t*)instance->memoryArena.data() + instance->rwOffset), exe->readWriteDataPool.data(), exe->readWriteDataSize);
}