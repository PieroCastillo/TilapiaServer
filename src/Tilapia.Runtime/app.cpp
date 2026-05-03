#include "common.hpp"
#include <cstdint>

import std;
import tilapia.irlib;
import tilapia.ops;
import tilapia.ops.time;
import tilapia.ops.simd;

using namespace Tilapia::IRLib;
using namespace Tilapia::Runtime;

std::vector<uint8_t> loadFile(const std::filesystem::path& path)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file)
        throw std::runtime_error("Can't open file");

    const auto size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        throw std::runtime_error("File reading error");

    return buffer;
}

int main(int argc, char** argv) {
    std::println("Tilapia Runtime v0.1");

    std::string asmPath;

    if (!(std::cin >> asmPath))
    {
        std::println("Invalid Input");
    }
    auto asmBytes = loadFile(asmPath);
    auto binDesc = loadDesc(asmBytes);
    if (!binDesc)
    {
        std::print("File Description Error");
        return -1;
    }

    /*
    execBinary = load(asmPath); // converts raw data to spec-valid IR Assembly

    validate(execBinary); // check caps
    -- validate stack registers (really important, stack overflow if dont)
    -- check capabilities
    -- check function arguments
    -- validate calls for dynamic libs & capabilities
    */

    auto exeRes = loadBin(asmBytes, binDesc.value());
    if (!exeRes)
    {
        std::print("Internal File Error");
        return -1;
    }

    binary executable = exeRes.value();
    Instance es; // execution state
    ConfigureInstance(&executable, &es, 4 * 1024 * 1024); // 4 MB arena
    es.isRunning = true;
    // TODO: impl memprotect for RO | instructions

    while (es.isRunning)
    {
        // fetch instruction
        const instruction& inst = executable.instructions[es.ip];

        // execute instruction
        switch (static_cast<coreOpcodes>(inst.opCode))
        {
        case coreOpcodes::nop: execute_nop(es, inst); break;
        case coreOpcodes::mov: execute_mov(es, inst); break;
        case coreOpcodes::li_i32: execute_li_i32(es, inst); break;
        case coreOpcodes::li_u32: execute_li_u32(es, inst); break;
        case coreOpcodes::li_f32: execute_li_f32(es, inst); break;
        case coreOpcodes::li64: execute_li64(es, inst); break;
        case coreOpcodes::load_u8: execute_load_u8(es, inst); break;
        case coreOpcodes::load_i16: execute_load_i16(es, inst); break;
        case coreOpcodes::load_i32: execute_load_i32(es, inst); break;
        case coreOpcodes::load_i64: execute_load_i64(es, inst); break;
        case coreOpcodes::load_f32: execute_load_f32(es, inst); break;
        case coreOpcodes::load_f64: execute_load_f64(es, inst); break;
        case coreOpcodes::store_u8: execute_store_u8(es, inst); break;
        case coreOpcodes::store_i16: execute_store_i16(es, inst); break;
        case coreOpcodes::store_i32: execute_store_i32(es, inst); break;
        case coreOpcodes::store_i64: execute_store_i64(es, inst); break;
        case coreOpcodes::store_f32: execute_store_f32(es, inst); break;
        case coreOpcodes::store_f64: execute_store_f64(es, inst); break;
        case coreOpcodes::s_addr: execute_s_addr(es, inst); break;
        case coreOpcodes::alloc: execute_alloc(es, inst); break;
        case coreOpcodes::free: execute_free(es, inst); break;
        case coreOpcodes::memcpy: execute_memcpy(es, inst); break;
        case coreOpcodes::submem: execute_submem(es, inst); break;
        case coreOpcodes::call: execute_call(es, inst); break;
        case coreOpcodes::call_cap: execute_call_cap(es, inst); break;
        case coreOpcodes::call_lib: execute_call_lib(es, inst); break;
        case coreOpcodes::ret: {
            if (es.callStack.empty()) [[unlikely]]
            {
                es.isRunning = false;
            }
            execute_ret(es, inst);
            break;
        }
        case coreOpcodes::jmp: execute_jmp(es, inst); break;
        case coreOpcodes::br_true: execute_br_true(es, inst); break;
        case coreOpcodes::br_false: execute_br_false(es, inst); break;
        case coreOpcodes::br_table: execute_br_table(es, inst); break;

        case coreOpcodes::add_i: execute_add_i(es, inst); break;
        case coreOpcodes::sub_i: execute_sub_i(es, inst); break;
        case coreOpcodes::mul_i: execute_mul_i(es, inst); break;
        case coreOpcodes::div_i: execute_div_i(es, inst); break;
        case coreOpcodes::mod_i: execute_mod_i(es, inst); break;

        case coreOpcodes::add_f: execute_add_f(es, inst); break;
        case coreOpcodes::sub_f: execute_sub_f(es, inst); break;
        case coreOpcodes::mul_f: execute_mul_f(es, inst); break;
        case coreOpcodes::div_f: execute_div_f(es, inst); break;

        case coreOpcodes::and_b: execute_and_b(es, inst); break;
        case coreOpcodes::or_b: execute_or_b(es, inst); break;
        case coreOpcodes::xor_b: execute_xor_b(es, inst); break;
        case coreOpcodes::not_b: execute_not_b(es, inst); break;
        case coreOpcodes::shl_b: execute_shl_b(es, inst); break;
        case coreOpcodes::shr_b: execute_shr_b(es, inst); break;

        case coreOpcodes::cmp_eq_i: execute_cmp_eq_i(es, inst); break;
        case coreOpcodes::cmp_ne_i: execute_cmp_ne_i(es, inst); break;
        case coreOpcodes::cmp_lt_i: execute_cmp_lt_i(es, inst); break;
        case coreOpcodes::cmp_gt_i: execute_cmp_gt_i(es, inst); break;

        case coreOpcodes::cmp_eq_f: execute_cmp_eq_f(es, inst); break;
        case coreOpcodes::cmp_lt_f: execute_cmp_lt_f(es, inst); break;
        case coreOpcodes::cmp_gt_f: execute_cmp_gt_f(es, inst); break;

        case coreOpcodes::now_monotonic: execute_now_monotonic(es, inst); break;
        case coreOpcodes::now_wallclock: execute_now_wallclock(es, inst); break;

        case coreOpcodes::vsetvl: execute_vsetvl(es, inst); break;
        case coreOpcodes::vload: execute_vload(es, inst); break;
        case coreOpcodes::vstore: execute_vstore(es, inst); break;
        case coreOpcodes::vgather: execute_vgather(es, inst); break;
        case coreOpcodes::vscatter: execute_vscatter(es, inst); break;
        case coreOpcodes::vbroadcast_s:execute_vbroadcast_s(es, inst); break;
        case coreOpcodes::vadd_i: execute_vadd_i(es, inst); break;
        case coreOpcodes::vsub_i: execute_vsub_i(es, inst); break;
        case coreOpcodes::vmul_i: execute_vmul_i(es, inst); break;
        case coreOpcodes::vdiv_i: execute_vdiv_i(es, inst); break;
        case coreOpcodes::vmod_i: execute_vmod_i(es, inst); break;
        case coreOpcodes::vmin_i: execute_vmin_i(es, inst); break;
        case coreOpcodes::vmax_i: execute_vmax_i(es, inst); break;
        case coreOpcodes::vabs_i: execute_vabs_i(es, inst); break;
        case coreOpcodes::vadd_vs_i: execute_vadd_vs_i(es, inst); break;
        case coreOpcodes::vsub_vs_i: execute_vsub_vs_i(es, inst); break;
        case coreOpcodes::vmul_vs_i: execute_vmul_vs_i(es, inst); break;
        case coreOpcodes::vdiv_vs_i: execute_vdiv_vs_i(es, inst); break;
        case coreOpcodes::vadd_f: execute_vadd_f(es, inst); break;
        case coreOpcodes::vsub_f: execute_vsub_f(es, inst); break;
        case coreOpcodes::vmul_f: execute_vmul_f(es, inst); break;
        case coreOpcodes::vdiv_f: execute_vdiv_f(es, inst); break;
        case coreOpcodes::vmin_f: execute_vmin_f(es, inst); break;
        case coreOpcodes::vmax_f: execute_vmax_f(es, inst); break;
        case coreOpcodes::vabs_f: execute_vabs_f(es, inst); break;
        case coreOpcodes::vsqrt_f: execute_vsqrt_f(es, inst); break;
        case coreOpcodes::vfma_f: execute_vfma_f(es, inst); break;
        case coreOpcodes::vfms_f: execute_vfms_f(es, inst); break;
        case coreOpcodes::vadd_vs_f: execute_vadd_vs_f(es, inst); break;
        case coreOpcodes::vmul_vs_f: execute_vmul_vs_f(es, inst); break;
        case coreOpcodes::vmul_vs_f_i: execute_vmul_vs_f_i(es, inst); break;
        case coreOpcodes::vand_b: execute_vand_b(es, inst); break;
        case coreOpcodes::vor_b: execute_vor_b(es, inst); break;
        case coreOpcodes::vxor_b: execute_vxor_b(es, inst); break;
        case coreOpcodes::vnot_b: execute_vnot_b(es, inst); break;
        case coreOpcodes::vshl_i: execute_vshl_i(es, inst); break;
        case coreOpcodes::vshr_i: execute_vshr_i(es, inst); break;
        case coreOpcodes::vsar_i: execute_vsar_i(es, inst); break;
        case coreOpcodes::vshl_vs_i: execute_vshl_vs_i(es, inst); break;
        case coreOpcodes::vcmp_eq_i: execute_vcmp_eq_i(es, inst); break;
        case coreOpcodes::vcmp_gt_i: execute_vcmp_gt_i(es, inst); break;
        case coreOpcodes::vcmp_lt_i: execute_vcmp_lt_i(es, inst); break;
        case coreOpcodes::vcmp_eq_f: execute_vcmp_eq_f(es, inst); break;
        case coreOpcodes::vcmp_gt_f: execute_vcmp_gt_f(es, inst); break;
        case coreOpcodes::vcmp_lt_f: execute_vcmp_lt_f(es, inst); break;
        case coreOpcodes::vblend_m: execute_vblend_m(es, inst); break;
        case coreOpcodes::vload_m: execute_vload_m(es, inst); break;
        case coreOpcodes::vstore_m: execute_vstore_m(es, inst); break;
        case coreOpcodes::vshuffle: execute_vshuffle(es, inst); break;
        case coreOpcodes::vpack: execute_vpack(es, inst); break;
        case coreOpcodes::vunpack: execute_vunpack(es, inst); break;
        case coreOpcodes::vreduce_add_i: execute_vreduce_add_i(es, inst); break;
        case coreOpcodes::vreduce_mul_i: execute_vreduce_mul_i(es, inst); break;
        case coreOpcodes::vreduce_add_f: execute_vreduce_add_f(es, inst); break;
        case coreOpcodes::vreduce_max_f: execute_vreduce_max_f(es, inst); break;
        }

        ++es.ip;
    }
    return 0;
}