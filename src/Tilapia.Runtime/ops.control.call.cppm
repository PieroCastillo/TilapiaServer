module;

#include "common.hpp"

export module tilapia.ops:control.call;
import tilapia.ir;
import tilapia.instance;

using namespace Tilapia::Runtime::IR;

export namespace Tilapia::Runtime
{
    ForceInline void execute_call(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_call_cap(Instance& es, const instruction& inst)
    {
        auto cap = inst.op1;
        auto funcID = inst.op2;
        auto firstRg = inst.op3;

        
    }

    ForceInline void execute_call_lib(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_ret(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_jmp(Instance& es, const instruction& inst)
    {

    }
}