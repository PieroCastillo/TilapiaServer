module;

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

#include "IR.hpp"
#include "Instance.hpp"
#include "common.hpp"

export module core:control;

#if defined(_MSC_VER)
#define ForceInline __forceinline
#elif defined(__clang__)
#define ForceInline __attribute__((always_inline)) inline
#elif defined(__GNUC__)
#define ForceInline __attribute__((always_inline)) inline
#else
#define ForceInline inline
#endif

using namespace TilapiaServer::Runtime;
using namespace TilapiaServer::Runtime::IR;

export namespace TilapiaServer::Runtime
{
    ForceInline void execute_nop(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_mov(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_li_i32(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_li_u32(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_li_f32(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_li64(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_load_u8(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_load_i16(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_load_i32(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_load_i64(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_load_f32(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_load_f64(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_store_u8(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_store_i16(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_store_i32(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_store_i64(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_store_f32(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_store_f64(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_s_addr(Instance& es, const instruction& inst)
    {

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

    ForceInline void execute_call(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_call_cap(Instance& es, const instruction& inst)
    {

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

    ForceInline void execute_br_true(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_br_false(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_br_table(Instance& es, const instruction& inst)
    {

    }
}