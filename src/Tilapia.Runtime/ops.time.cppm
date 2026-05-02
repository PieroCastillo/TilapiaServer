module;

#include "common.hpp"

export module tilapia.ops.time;
import tilapia.irlib;

using namespace Tilapia::IRLib;

export namespace Tilapia::Runtime
{
    ForceInline void execute_now_monotonic(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_now_wallclock(Instance& es, const instruction& inst)
    {

    }
};