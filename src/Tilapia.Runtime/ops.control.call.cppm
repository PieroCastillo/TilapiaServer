module;

// project headers
#include "common.hpp"
#include <iostream>
#include <print>
#include <string_view>

// project headers
#include "common.hpp"

export module tilapia.ops:control.call;
import tilapia.irlib;
import tilapia.handlers;

using namespace Tilapia::IRLib;

export namespace Tilapia::Runtime
{
    ForceInline void execute_call(Instance& es, const instruction& inst)
    {
        
    }

    ForceInline void execute_call_cap(Instance& es, const instruction& inst)
    {
        auto cap = inst.op1;
        auto funcID = static_cast<coreCalls>(inst.op2);
        auto firstRg = inst.op3;

        switch (funcID)
        {
        case coreCalls::print_str:
        {
            auto [ptr, size] = ResolveFatptr(&es, firstRg); // Rg contains a fatPtr
            std::string_view text(reinterpret_cast<const char*>(ptr), size);
            std::print("{}", text);
            break;
        }
        default:
            handleNotImplementedYet();
            break;
        }
    }

    ForceInline void execute_call_lib(Instance& es, const instruction& inst)
    {

    }

    ForceInline void execute_ret(Instance& es, const instruction& inst)
    {
        if (es.callStack.empty()) [[unlikely]]
        {
            es.isRunning = false;
        }
    }

    ForceInline void execute_jmp(Instance& es, const instruction& inst)
    {

    }
}