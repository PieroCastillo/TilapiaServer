module;

// project headers
#include "common.hpp"

export module tilapia.ops:control.mem;
import tilapia.irlib;

using namespace Tilapia::IRLib;

export namespace Tilapia::Runtime
{
    ForceInline void execute_alloc_bs(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_alloc_ro(Instance& es, const instruction& inst)
    {
        // input
        auto dstRg = inst.op1;
        auto dataIdx = inst.op2;

        auto dataEntry = es.roData[dataIdx];
        auto dataPtr = &es.roStorage[dataEntry.dataOffset];

        // alloc handle
        auto memVw = MemoryView{ dataPtr, dataEntry.size, MemFlag_Read, MemValue_syncDataIdx_NO_SYNC, dataEntry.dataOffset, 0 };
    
        // output
        es.valueStack[es.bp + inst.op1] = AllocFatptr(&es, memVw);
    }

    ForceInline void execute_alloc_rw(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_alloc_hp(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_free(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_memcpy(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_memset(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_memmove(Instance& es, const instruction& inst)
    {

    }
}