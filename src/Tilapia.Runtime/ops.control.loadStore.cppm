module;

#include <bit>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "common.hpp"

export module tilapia.ops:control.loadStore;
import tilapia.irlib;
import tilapia.handlers;

using namespace Tilapia::IRLib;

export namespace Tilapia::Runtime
{
    inline auto loadGetPtr(Instance& es, const instruction& inst) -> uint8_t*
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];
        uint32_t memIdx = fatPtr << 32;
        uint32_t memGen = fatPtr & 0xFFFFFF;

        if (es.viewsGenerations[memIdx] != memGen) [[unlikely]]
        {
            handleUseAfterFree();
            return nullptr;
        }

        auto& vw = es.views[memIdx];
        if (vw.size < sizeof(uint8_t) || valOffset > vw.size - sizeof(uint8_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return nullptr;
        }

        return vw.cachedPtr;
    }

    inline auto storeGetPtr(Instance& es, const instruction& inst) -> uint8_t*
    {
        uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
        uint32_t valOffset = es.valueStack[es.bp + inst.op3];
        uint32_t memIdx = fatPtr << 32;
        uint32_t memGen = fatPtr & 0xFFFFFF;

        if (es.viewsGenerations[memIdx] != memGen) [[unlikely]]
        {
            handleUseAfterFree();
            return nullptr;
        }

        auto& vw = es.views[memIdx];
        if (vw.size < sizeof(uint8_t) || valOffset > vw.size - sizeof(uint8_t)) [[unlikely]]
        {
            handleOutOfBounds();
            return nullptr;
        }

        return vw.cachedPtr;
    }

    ForceInline void execute_load_u8(Instance& es, const instruction& inst)
    {
        auto ptr = loadGetPtr(es, inst);
        memcpy(&es.valueStack[es.bp + inst.op1], ptr, sizeof(uint8_t));
    }

    ForceInline void execute_load_i16(Instance& es, const instruction& inst)
    {
        auto ptr = loadGetPtr(es, inst);
        memcpy(&es.valueStack[es.bp + inst.op1], ptr, sizeof(uint16_t));
    }

    ForceInline void execute_load_i32(Instance& es, const instruction& inst)
    {
        auto ptr = loadGetPtr(es, inst);
        memcpy(&es.valueStack[es.bp + inst.op1], ptr, sizeof(uint32_t));
    }

    ForceInline void execute_load_i64(Instance& es, const instruction& inst)
    {
        auto ptr = loadGetPtr(es, inst);
        memcpy(&es.valueStack[es.bp + inst.op1], ptr, sizeof(uint64_t));
    }

    ForceInline void execute_load_f32(Instance& es, const instruction& inst)
    {
        auto ptr = loadGetPtr(es, inst);

        float val;
        memcpy(&val, ptr, sizeof(float));
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(static_cast<double>(val));
    }

    ForceInline void execute_load_f64(Instance& es, const instruction& inst)
    {
        auto ptr = loadGetPtr(es, inst);

        double val;
        memcpy(&val, ptr, sizeof(double));
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val);
    }

    ForceInline void execute_store_u8(Instance& es, const instruction& inst)
    {
        auto ptr = storeGetPtr(es, inst);

        uint8_t val = static_cast<uint8_t>(es.valueStack[es.bp + inst.op2]);
        memcpy(ptr, &val, sizeof(uint8_t));
    }

    ForceInline void execute_store_i16(Instance& es, const instruction& inst)
    {   
        auto ptr = storeGetPtr(es, inst);

        uint16_t val = static_cast<uint16_t>(es.valueStack[es.bp + inst.op2]);
        memcpy(ptr, &val, sizeof(uint16_t));
    }

    ForceInline void execute_store_i32(Instance& es, const instruction& inst)
    {
        auto ptr = storeGetPtr(es, inst);

        uint32_t val = static_cast<uint32_t>(es.valueStack[es.bp + inst.op2]);
        memcpy(ptr, &val, sizeof(uint32_t));
    }

    ForceInline void execute_store_i64(Instance& es, const instruction& inst)
    {
        auto ptr = storeGetPtr(es, inst);

        uint64_t val = es.valueStack[es.bp + inst.op2];
        memcpy(ptr, &val, sizeof(uint64_t));
    }

    ForceInline void execute_store_f32(Instance& es, const instruction& inst)
    {
        auto ptr = storeGetPtr(es, inst);

        double doubleVal = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        float val = static_cast<float>(doubleVal);

        memcpy(ptr, &val, sizeof(float));
    }

    ForceInline void execute_store_f64(Instance& es, const instruction& inst)
    {
        auto ptr = storeGetPtr(es, inst);
     
        uint64_t val = es.valueStack[es.bp + inst.op2];
        memcpy(ptr, &val, sizeof(double));
    }
}