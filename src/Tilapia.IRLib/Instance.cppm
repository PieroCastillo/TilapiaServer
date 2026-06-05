module;

#include <cstdint>
#include <cstdlib>
#include <limits>
#include <unordered_map>
#include <vector>

export module tilapia.irlib:instance;
import :ir;
import :utils;

export namespace Tilapia::IRLib
{
    constexpr uint32_t MemFlag_Read = 0x1;
    constexpr uint32_t MemFlag_Write = 0x2;
    constexpr uint32_t MemFlag_File = 0x4;
    constexpr uint32_t MemFlag_ThreadShared = 0x8;
    constexpr uint32_t MemFlag_InternalSynchronized = 0x10;
    constexpr uint32_t MemValue_syncDataIdx_NO_SYNC = (std::numeric_limits<uint32_t>::max)();

    struct SyncData
    {

    };

    struct FileData
    {
        uint64_t fileDescriptor;
        uint64_t fileMapping;
        uint64_t filePtr;
    };

    struct MemoryView
    {
        uint8_t* cachedPtr;
        uint32_t size;
        uint32_t flags;
        uint32_t syncDataIdx;
        // cold
        uint32_t regionOffset;
        uint32_t regionIdx;
    };

    struct MemoryRegion
    {
        uint32_t regionSize; // in bytes
        uint8_t* basePtr;
        uint32_t flags;
        // optional
        uint32_t fileMapIdx;
    };

    struct CallFrame
    {
        uint32_t returnIP;
        uint32_t returnBP;
    };

    /**
     * 0x0 = RO
     * 0x1 = RW
     * 0x3 = BSS
     */

    struct Instance
    {
        std::vector<uint64_t> valueStack;
        std::vector<CallFrame> callStack;

        std::vector<MemoryRegion> regions;

        std::vector<MemoryView> views;
        std::vector<uint32_t> viewsGenerations;
        std::vector<uint32_t> viewsFreeIndexList;

        std::vector<FileData> fileDatas;
        std::vector<SyncData> syncDatas;

        std::vector<uint8_t> roStorage;
        std::vector<uint8_t> rwStorage;
        std::vector<uint8_t> bssStorage;
        std::vector<uint8_t> heapStorage;

        std::vector<dataEntry> roData;
        std::vector<dataEntry> rwData;

        uint32_t rwOffset, bssOffset, heapOffset;
        uint32_t roSize, rwSize, bssSize, heapSize;
        uint32_t arenaOffset = 0;

        uint32_t ip = 0; // instruction ptr
        uint32_t bp = 0; // base ptr
        uint32_t sp = 0; // stack ptr

        bool isRunning = false;
        int32_t exitCode = 0;
    };

    void ConfigureInstance(binary* exe, Instance* instance, uint32_t arenaSize)
    {
        constexpr uint32_t align = 64;
        instance->ip = exe->header.entrypointOffset;
        instance->valueStack.resize(8192); // 8192 variables
        instance->callStack.reserve(1024); // depth limit

        instance->roData = exe->readOnlyData;
        instance->rwData = exe->readWriteData;

        instance->roStorage.resize(alignUp(exe->readOnlyDataSize, align));
        instance->rwStorage.resize(alignUp(exe->readWriteDataSize, align));
        instance->bssStorage.resize(alignUp(exe->uninitializedDataSize, align), 0);
        instance->heapStorage.resize(alignUp(arenaSize, align), 0);

        MemoryRegion roRegion = { instance->roStorage.size(), instance->roStorage.data(), MemFlag_Read };
        MemoryRegion rwRegion = { instance->rwStorage.size(), instance->rwStorage.data(), MemFlag_Read | MemFlag_Write };
        MemoryRegion bssRegion = { instance->bssStorage.size(), instance->bssStorage.data(), MemFlag_Read | MemFlag_Write };
        MemoryRegion heapRegion = { instance->heapStorage.size(), instance->heapStorage.data(), MemFlag_Read | MemFlag_Write };

        instance->regions.push_back(roRegion);
        instance->regions.push_back(rwRegion);
        instance->regions.push_back(bssRegion);
        instance->regions.push_back(heapRegion);

        // copy
        memcpy(instance->roStorage.data(), exe->readOnlyDataPool.data(), exe->readOnlyDataPool.size());
        memcpy(instance->rwStorage.data(), exe->readWriteDataPool.data(), exe->readWriteDataPool.size());
    }

    inline auto ResolveFatptr(Instance* es, uint32_t rg) -> std::tuple<uint8_t*, uint32_t>
    {
        uint64_t fatPtr = es->valueStack[rg];
        uint32_t memIdx = fatPtr << 32;
        uint32_t memGen = fatPtr & 0xFFFFFF;

        if (es->viewsGenerations[memIdx] != memGen) [[unlikely]]
            return { nullptr, 0 };

        auto& vw = es->views[memIdx];
        if (vw.size < sizeof(uint8_t)) [[unlikely]]
            return { nullptr, 0 };

        return { vw.cachedPtr, vw.size };
    }

    inline auto AllocFatptr(Instance* instance, const MemoryView& view) -> uint64_t
    {
        uint32_t index;

        if (!instance->viewsFreeIndexList.empty())
        {
            index = instance->viewsFreeIndexList.back();
            instance->viewsFreeIndexList.pop_back();

            instance->views[index] = view;
        }
        else
        {
            index = static_cast<uint32_t>(instance->views.size());

            instance->views.push_back(view);
            instance->viewsGenerations.push_back(0);
        }

        uint64_t fatPtr = ((uint64_t)index << 32) | (uint64_t)instance->viewsGenerations[index];
        return fatPtr;
    }

    inline void FreeFatptr(Instance* instance, uint64_t fatPtr)
    {
        uint32_t memIdx = fatPtr << 32;
        uint32_t memGen = fatPtr & 0xFFFFFF;

        if (memIdx >= instance->views.size())
            return;

        if (instance->viewsGenerations[memIdx] != memGen)
            return;

        ++instance->viewsGenerations[memIdx];
        instance->viewsFreeIndexList.push_back(memIdx);
    }
};