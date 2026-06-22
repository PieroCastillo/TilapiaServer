/*
Created by @PieroCastillo on 2026-06-20
*/
module;

#include <atomic>
#include <new>
#include <type_traits>

export module tilapia.protocol:fastsharedring;
import tilapia.platform;
import :userqueues;

#define NoShare alignas(std::hardware_destructive_interference_size)

export namespace Tilapia::Protocol
{
    template<typename T>
    concept TrivialCopy = std::is_trivially_copyable_v<T>;

    struct RingHeader
    {
        NoShare std::atomic<uint32_t> readIdx;
        NoShare std::atomic<uint32_t> writeIdx;
        uint32_t capacity;
        uint32_t stride;
    };

    struct FastSharedRingCreateInfo
    {

    };

    struct FastSharedRingOpenInfo
    {

    };

    template<TrivialCopy T>
    class FastSharedRing
    {
    private:
        Tilapia::Platform::SharedMemory shMem;
        uint8_t* shMemPtr;

        RingHeader* ringHeader; // = (RingHeader*)shMemPtr;
        T* ringBuff; // = (uint8_t*)shMemPtr + sizeof(T);
        uint32_t capacity; // = ringHeader->capacity;

        void setup()
        {
            shMemPtr = shMem.data;
            ringHeader = (RingHeader*)shMemPtr;
            ringBuff = (uint8_t*)shMemPtr + sizeof(T);
            capacity = ringHeader->capacity;
            if (!shMem.isOwner)
                return;
            ringHeader->readIdx = 0;
            ringHeader->writeIdx = 0;
        }
    public:
        explicit FastSharedRing(uint32_t count)
        {
            shMemPtr = Tilapia::Platform::sharedAlloc(sizeof(RingHeader) + (count * sizeof(T)));
            setup();
        };

        explicit FastSharedRing(uint64_t handle, uint32_t count)
        {
            shMemPtr = Tilapia::Platform::sharedOpen(handle, sizeof(RingHeader) + (count * sizeof(T)));
            setup();
        };

        void Push(const T& item)
        {
            auto write = ringHeader->writeIdx;
            auto nextWrite = ringHeader->writeIdx + 1;

            if (nextWrite == capacity)
                nextWrite = 0;

            if (nextWrite == ringHeader->readIdx.load(std::memory_order_acquire))
                return;

            ringBuff[write] = item;
            ringHeader->writeIdx.store(nextWrite);
        }

        auto Pop() -> T
        {
            if (ringHeader->readIdx == ringHeader->writeIdx.load(std::memory_order_acquire))
                return {};

            auto item = *ringBuff[ringHeader->readIdx];

            auto nextRead = ringHeader->readIdx + 1;

            if (nextRead == capacity)
                nextRead = 0;

            ringHeader->readIdx.store(nextRead, std::memory_order_release);
            return item;
        }

        auto IsEmpty() -> bool
        {
            auto ringHeader = ((RingHeader*)shMemPtr);
            return ringHeader->readIdx == ringHeader->writeIdx;
        }

        auto IsFull() -> bool
        {
            auto ringHeader = ((RingHeader*)shMemPtr);
            return (ringHeader->readIdx - ringHeader->writeIdx) == ringHeader->capacity;
        }

        auto Size() -> uint32_t
        {
            return (ringHeader->writeIDx - ringHeader->readIdx);
        }
    };
};