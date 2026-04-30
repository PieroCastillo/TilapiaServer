module;

#include "common.hpp"

export module tilapia.ops:alu.bitwise;
import tilapia.ir;
import tilapia.instance;

using namespace Tilapia::Runtime::IR;

export namespace Tilapia::Runtime
{
    // ALU BITWISE/LOGIC : 0x0003
    ForceInline void execute_and_b(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = (val1 & val2);
    }

    ForceInline void execute_or_b(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = (val1 | val2);
    }

    ForceInline void execute_xor_b(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = (val1 ^ val2);
    }

    ForceInline void execute_not_b(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        es.valueStack[es.bp + inst.op1] = !(val1);
    }

    ForceInline void execute_shl_b(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = (val1 << (val2 & 0x3F)); // bounds check
    }

    ForceInline void execute_shr_b(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = (val1 >> val2);
    }
}