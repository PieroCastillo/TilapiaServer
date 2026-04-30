module;

#include <bit>
#include <cstdint>
#include "common.hpp"

export module tilapia.ops:alu.f;
import tilapia.ir;
import tilapia.instance;
import tilapia.handlers;

using namespace Tilapia::Runtime::IR;

export namespace Tilapia::Runtime
{
    // ALU FLOAT : 0x0002
    ForceInline void execute_add_f(Instance& es, const instruction& inst)
    {
        auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 + val2);
    }

    ForceInline void execute_sub_f(Instance& es, const instruction& inst)
    {
        auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 - val2);
    }

    ForceInline void execute_mul_f(Instance& es, const instruction& inst)
    {
        auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 * val2);
    }

    ForceInline void execute_div_f(Instance& es, const instruction& inst)
    {
        auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);

        if (val2 == 0.0) [[unlikely]]
        {
            handleZeroDivision();
            return;
        }

        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 / val2);
    }
}