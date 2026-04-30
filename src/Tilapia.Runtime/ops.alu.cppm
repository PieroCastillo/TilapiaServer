module;

#include "common.hpp"

export module tilapia.ops:alu;
import tilapia.ir;
import tilapia.instance;

using namespace Tilapia::Runtime::IR;

export namespace Tilapia::Runtime
{
    // ALU INT : 0x0001
    ForceInline void execute_add_i(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_sub_i(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_mul_i(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_div_i(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_mod_i(Instance& es, const instruction& inst)
    {

    }

    // ALU FLOAT : 0x0002
    ForceInline void execute_add_f(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_sub_f(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_mul_f(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_div_f(Instance& es, const instruction& inst)
    {

    }


    // ALU BITWISE/LOGIC : 0x0003
    ForceInline void execute_and_b(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_or_b(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_xor_b(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_not_b(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_shl_b(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_shr_b(Instance& es, const instruction& inst)
    {

    }


    // ALU COMP INT : 0x0004
    ForceInline void execute_cmp_eq_i(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_cmp_ne_i(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_cmp_lt_i(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_cmp_gt_i(Instance& es, const instruction& inst)
    {

    }

    // ALU COMP FLOAT : 0x0005
    ForceInline void execute_cmp_eq_f(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_cmp_lt_f(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_cmp_gt_f(Instance& es, const instruction& inst)
    {

    }
}