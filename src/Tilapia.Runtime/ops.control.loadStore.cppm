module;

#include <bit>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "common.hpp"

export module tilapia.ops:control.loadStore;
import tilapia.handlers;
import tilapia.ir;
import tilapia.instance;

using namespace Tilapia::Runtime::IR;

export namespace Tilapia::Runtime
{
    ForceInline void execute_load_u8(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint8_t) || valOffset > memSize - sizeof(uint8_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint8_t val;
        memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint8_t));
        es.valueStack[es.bp + inst.op1] = val;
    }

    ForceInline void execute_load_i16(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint16_t) || valOffset > memSize - sizeof(uint16_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint16_t val;
        memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint16_t));
        es.valueStack[es.bp + inst.op1] = val;
    }

    ForceInline void execute_load_i32(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint32_t) || valOffset > memSize - sizeof(uint32_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint32_t val;
        std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint32_t));
        es.valueStack[es.bp + inst.op1] = val;
    }

    ForceInline void execute_load_i64(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint64_t) || valOffset > memSize - sizeof(uint64_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint64_t val;
        std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint64_t));
        es.valueStack[es.bp + inst.op1] = val;
    }

    ForceInline void execute_load_f32(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(float) || valOffset > memSize - sizeof(float)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        float val;
        std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(float));
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(static_cast<double>(val));
    }

    ForceInline void execute_load_f64(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(double) || valOffset > memSize - sizeof(double)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        double val;
        std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(double));
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val);
    }

    ForceInline void execute_store_u8(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint8_t) || valOffset > memSize - sizeof(uint8_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint8_t val = static_cast<uint8_t>(es.valueStack[es.bp + inst.op2]);
        std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint8_t));
    }

    ForceInline void execute_store_i16(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint16_t) || valOffset > memSize - sizeof(uint16_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint16_t val = static_cast<uint16_t>(es.valueStack[es.bp + inst.op2]);
        std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint16_t));
    }

    ForceInline void execute_store_i32(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint32_t) || valOffset > memSize - sizeof(uint32_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint32_t val = static_cast<uint32_t>(es.valueStack[es.bp + inst.op2]);
        std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint32_t));
    }

    ForceInline void execute_store_i64(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(uint64_t) || valOffset > memSize - sizeof(uint64_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint64_t val = es.valueStack[es.bp + inst.op2];
        std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint64_t));
    }

    ForceInline void execute_store_f32(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(float) || valOffset > memSize - sizeof(float)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        double doubleVal = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        float val = static_cast<float>(doubleVal);

        std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(float));
    }

    ForceInline void execute_store_f64(Instance& es, const instruction& inst)
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
        uint32_t memSize = fatPtr >> 32;
        uint32_t memOffset = fatPtr & 0xFFFFFFFF;
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];

        if (memSize < sizeof(double) || valOffset > memSize - sizeof(double)) [[unlikely]]
        {
            handleOutOfBounds();
            return;
        }

        uint64_t val = es.valueStack[es.bp + inst.op2];
        std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(double));
    }
}