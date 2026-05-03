module;

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <expected>
#include <ranges>
#include <span>
#include <string>
#include <print>
#include <type_traits>
#include <vector>

export module tilapia.printInst;
import tilapia.irlib;

using namespace Tilapia::IRLib;

export void printInstruction(const Tilapia::IRLib::instruction& inst, size_t pc)
{
    using namespace Tilapia::IRLib;

    auto op = static_cast<coreOpcodes>(inst.opCode);

    std::print("[{:04}] {:<18}", pc, to_string(op));

    switch (op)
    {
    case coreOpcodes::nop:
        std::println();
        break;

    case coreOpcodes::mov:
        std::println("{}, {}", reg(inst.op1), reg(inst.op2));
        break;

    case coreOpcodes::li_i32:
        std::println("{}, {}", reg(inst.op1), imm_i32(inst.op2));
        break;

    case coreOpcodes::li_u32:
        std::println("{}, {}", reg(inst.op1), imm_u32(inst.op2));
        break;

    case coreOpcodes::li_f32:
        std::println("{}, {}", reg(inst.op1), imm_f32(inst.op2));
        break;

    case coreOpcodes::li64:
        std::println("{}, {}", reg(inst.op1), imm_u64(inst.op2, inst.op3));
        break;

    case coreOpcodes::load_u8:
    case coreOpcodes::load_i16:
    case coreOpcodes::load_i32:
    case coreOpcodes::load_i64:
    case coreOpcodes::load_f32:
    case coreOpcodes::load_f64:
        std::println("{}, [{}]", reg(inst.op1), reg(inst.op2));
        break;

    case coreOpcodes::store_u8:
    case coreOpcodes::store_i16:
    case coreOpcodes::store_i32:
    case coreOpcodes::store_i64:
    case coreOpcodes::store_f32:
    case coreOpcodes::store_f64:
        std::println("[{}], {}", reg(inst.op1), reg(inst.op2));
        break;

    case coreOpcodes::s_addr:
        std::println("{}, &{}", reg(inst.op1), reg(inst.op2));
        break;

    case coreOpcodes::alloc:
        std::println("{}, size={}, align={}", reg(inst.op1), imm_u32(inst.op2), imm_u32(inst.op3));
        break;

    case coreOpcodes::free:
        std::println("{}", reg(inst.op1));
        break;

    case coreOpcodes::memcpy:
        std::println("dst={}, src={}, bytes={}", reg(inst.op1), reg(inst.op2), imm_u32(inst.op3));
        break;

    case coreOpcodes::submem:
        std::println("{}, {}, offset={}", reg(inst.op1), reg(inst.op2), imm_u32(inst.op3));
        break;

    case coreOpcodes::call:
        std::println("fn={}, arg={}", inst.op1, reg(inst.op2));
        break;

    case coreOpcodes::call_cap:
        std::println("cap={}, call={}, first arg={}",
            to_string(static_cast<coreCaps>(inst.op1)),
            to_string(static_cast<coreCalls>(inst.op2)),
            reg(inst.op3));
        break;

    case coreOpcodes::call_lib:
        std::println("lib={}, sym={}, argc={}", imm_u32(inst.op1), imm_u32(inst.op2), reg(inst.op3));
        break;

    case coreOpcodes::ret:
        break;

    case coreOpcodes::jmp:
        std::println("-> {}", imm_u32(inst.op1));
        break;

    case coreOpcodes::br_true:
        std::println("{}, -> {}", reg(inst.op1), imm_u32(inst.op2));
        break;

    case coreOpcodes::br_false:
        std::println("{}, -> {}", reg(inst.op1), imm_u32(inst.op2));
        break;

    case coreOpcodes::br_table:
        std::println("index={}, table={}", reg(inst.op1), imm_u32(inst.op2));
        break;

    case coreOpcodes::add_i:
    case coreOpcodes::sub_i:
    case coreOpcodes::mul_i:
    case coreOpcodes::div_i:
    case coreOpcodes::mod_i:
        std::println("{}, {}, {}", reg(inst.op1), reg(inst.op2), reg(inst.op3));
        break;

    case coreOpcodes::add_f:
    case coreOpcodes::sub_f:
    case coreOpcodes::mul_f:
    case coreOpcodes::div_f:
        std::println("{}, {}, {}", reg(inst.op1), reg(inst.op2), reg(inst.op3));
        break;

    case coreOpcodes::and_b:
    case coreOpcodes::or_b:
    case coreOpcodes::xor_b:
    case coreOpcodes::shl_b:
    case coreOpcodes::shr_b:
        std::println("{}, {}, {}", reg(inst.op1), reg(inst.op2), reg(inst.op3));
        break;

    case coreOpcodes::not_b:
        std::println("{}, {}", reg(inst.op1), reg(inst.op2));
        break;

    case coreOpcodes::cmp_eq_i:
    case coreOpcodes::cmp_ne_i:
    case coreOpcodes::cmp_lt_i:
    case coreOpcodes::cmp_gt_i:
        std::println("{}, {}, {}", reg(inst.op1), reg(inst.op2), reg(inst.op3));
        break;

    case coreOpcodes::cmp_eq_f:
    case coreOpcodes::cmp_lt_f:
    case coreOpcodes::cmp_gt_f:
        std::println("{}, {}, {}", reg(inst.op1), reg(inst.op2), reg(inst.op3));
        break;

    case coreOpcodes::now_monotonic:
    case coreOpcodes::now_wallclock:
        std::println("{}", reg(inst.op1));
        break;


    case coreOpcodes::vsetvl:
        std::println("vl={}", imm_u32(inst.op1));
        break;

    default:
        std::println("{}, {}, {}", imm_u32(inst.op1), imm_u32(inst.op2), imm_u32(inst.op3));
        break;
    }
}