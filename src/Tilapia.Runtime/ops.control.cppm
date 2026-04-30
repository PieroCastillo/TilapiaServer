module;

#include <bit>
#include <cstdint>
#include "common.hpp"

export module tilapia.ops:control;
import tilapia.ir;
import tilapia.instance;

using namespace Tilapia::Runtime::IR;

export namespace Tilapia::Runtime
{
    ForceInline void execute_nop(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_mov(Instance& es, const instruction& inst)
    {
        es.valueStack[es.bp + inst.op1] = es.valueStack[es.bp + inst.op2];
    }

    ForceInline void execute_li_i32(Instance& es, const instruction& inst)
    {
        es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(inst.op2)));
    }

    ForceInline void execute_li_u32(Instance& es, const instruction& inst)
    {
        es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(inst.op2);
    }

    ForceInline void execute_li_f32(Instance& es, const instruction& inst)
    {
        auto raw_f32 = std::bit_cast<float>(inst.op2);
        es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(static_cast<double>(raw_f32));
    }

    ForceInline void execute_li64(Instance& es, const instruction& inst)
    {
        es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(inst.op2) << 32 | static_cast<uint64_t>(inst.op3);
    }
}