module;

#include "common.hpp"

export module tilapia.ops:control.mem;
import tilapia.irlib;

using namespace Tilapia::IRLib;

export namespace Tilapia::Runtime
{
    ForceInline void execute_salloc(Instance& es, const instruction& inst)
    {
        auto dataId = es.valueStack[inst.op2];
        auto dataSrc = es.valueStack[inst.op3];
        

        auto valRg = es.valueStack[inst.op1];
    }

    ForceInline void execute_alloc(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_free(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_memcpy(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_submem(Instance& es, const instruction& inst)
    {

    }
}