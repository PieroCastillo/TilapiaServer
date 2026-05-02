module;

#include <bit>
#include <cstdint>
#include <limits>
#include "common.hpp"

export module tilapia.ops:alu.i;
import tilapia.irlib;
import tilapia.handlers;

using namespace Tilapia::IRLib;

export namespace Tilapia::Runtime
{
    // ALU INT : 0x0001
    ForceInline void execute_add_i(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = val1 + val2;
    }

    ForceInline void execute_sub_i(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = val1 - val2;
    }

    ForceInline void execute_mul_i(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = val1 * val2;
    }

    ForceInline void execute_div_i(Instance& es, const instruction& inst)
    {
        auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
        auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);

        if (val2 == 0) [[unlikely]]
        {
            handleZeroDivision();
            return;
        }

        if (val1 == std::numeric_limits<int64_t>::min() && val2 == -1) [[unlikely]]
        {
            handleOverflow();
            return;
        }

        es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 / val2);
    }

    ForceInline void execute_mod_i(Instance& es, const instruction& inst)
    {
        auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
        auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);

        if (val2 == 0) [[unlikely]]
        {
            handleZeroDivision();
            return;
        }

        if (val1 == std::numeric_limits<int64_t>::min() && val2 == -1) [[unlikely]]
        {
            es.valueStack[es.bp + inst.op1] = 0;
            return;
        }

        es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 % val2);
    }
}