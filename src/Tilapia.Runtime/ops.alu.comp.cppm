module;

#include <bit>
#include <cstdint>
#include "common.hpp"

export module tilapia.ops:alu.comp;
import tilapia.irlib;

using namespace Tilapia::IRLib;

export namespace Tilapia::Runtime
{
    // ALU COMP INT : 0x0004
    ForceInline void execute_cmp_eq_i(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = (val1 == val2);
    }

    ForceInline void execute_cmp_ne_i(Instance& es, const instruction& inst)
    {
        auto val1 = es.valueStack[es.bp + inst.op2];
        auto val2 = es.valueStack[es.bp + inst.op3];
        es.valueStack[es.bp + inst.op1] = (val1 != val2);
    }

    ForceInline void execute_cmp_lt_i(Instance& es, const instruction& inst)
    {
        auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
        auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 < val2);
    }

    ForceInline void execute_cmp_gt_i(Instance& es, const instruction& inst)
    {
        auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
        auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 > val2);
    }

    // ALU COMP FLOAT : 0x0005
    ForceInline void execute_cmp_eq_f(Instance& es, const instruction& inst)
    {
        auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = (val1 == val2);
    }

    ForceInline void execute_cmp_lt_f(Instance& es, const instruction& inst)
    {
        auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = (val1 < val2);
    }

    ForceInline void execute_cmp_gt_f(Instance& es, const instruction& inst)
    {
        auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
        auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
        es.valueStack[es.bp + inst.op1] = (val1 > val2);
    }
}