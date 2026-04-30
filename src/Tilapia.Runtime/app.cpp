#include "common.hpp"
#include <cstdint>

import std;
import tilapia.ir;
import tilapia.instance;
import tilapia.ops;

using namespace Tilapia::Runtime;
using namespace Tilapia::Runtime::IR;

void handleNotImplementedYet()
{

}

void handleOverflow()
{

}

void handleZeroDivision()
{

}

void handleOutOfBounds()
{

}

int main(int argc, char** argv) {
    std::println("Tilapia Runtime v0.1");

    std::string asmPath;

    if (!(std::cin >> asmPath))
    {
        std::println("Invalid Input");
    }

    /*
    execBinary = load(asmPath); // converts raw data to spec-valid IR Assembly
    validate(execBinary); // check caps
    -- validate stack registers (really important, stack overflow if dont)
    -- check capabilities
    -- check function arguments
    -- validate calls for dynamic libs & capabilities
    while()0x0400IR
    */

    binary executable;
    Instance es; // execution state
    ConfigureInstance(&executable, &es, 4 * 1024 * 1024); // 4 MB arena

    auto& program = executable.instructions;
    while (es.isRunning)
    {
        // fetch instruction
        const IR::instruction& inst = executable.instructions[es.ip++];
        uint32_t op = (inst.capId << 16) | inst.opCode;

        // execute instruction
        switch (static_cast<IR::coreOpcodes>(op))
        {
        case IR::coreOpcodes::nop: execute_nop(es, inst);
            break;
        case IR::coreOpcodes::mov: // dstRg, srcRg
            es.valueStack[es.bp + inst.op1] = es.valueStack[es.bp + inst.op2];
            break;
        case IR::coreOpcodes::li_i32: // dstRg, low_imm
            es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(inst.op2)));
            break;
        case IR::coreOpcodes::li_u32: // dstRg, low_imm
            es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(inst.op2);
            break;
        case IR::coreOpcodes::li_f32: // dstRg, low_imm
        {
            float raw_f32 = std::bit_cast<float>(inst.op2);
            es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(static_cast<double>(raw_f32));
            break;
        }
        case IR::coreOpcodes::li64: // dstRg, high_imm, low_imm
            es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(inst.op2) << 32 | static_cast<uint64_t>(inst.op3);
            break;
        case IR::coreOpcodes::load_u8: // dstRg, srcPtrRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint8_t) || valOffset > memSize - sizeof(uint8_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint8_t val;
            std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint8_t));
            es.valueStack[es.bp + inst.op1] = val;
            break;
        }
        case IR::coreOpcodes::load_i16: // dstRg, srcPtrRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint16_t) || valOffset > memSize - sizeof(uint16_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint16_t val;
            std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint16_t));
            es.valueStack[es.bp + inst.op1] = val;
            break;
        }
        case IR::coreOpcodes::load_i32: // dstRg, srcPtrRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint32_t) || valOffset > memSize - sizeof(uint32_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint32_t val;
            std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint32_t));
            es.valueStack[es.bp + inst.op1] = val;
            break;
        }
        case IR::coreOpcodes::load_i64: // dstRg, srcPtrRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint64_t) || valOffset > memSize - sizeof(uint64_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint64_t val;
            std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(uint64_t));
            es.valueStack[es.bp + inst.op1] = val;
            break;
        }
        case IR::coreOpcodes::load_f32: // dstRg, srcPtrRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(float) || valOffset > memSize - sizeof(float)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            float val;
            std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(float));
            es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(static_cast<double>(val));
            break;
        }
        case IR::coreOpcodes::load_f64: // dstRg, srcPtrRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op2];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(double) || valOffset > memSize - sizeof(double)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            double val;
            std::memcpy(&val, &es.memoryArena[memOffset + valOffset], sizeof(double));
            es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val);
            break;
        }
        case IR::coreOpcodes::store_u8: // dstPtrRg, srcRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint8_t) || valOffset > memSize - sizeof(uint8_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint8_t val = static_cast<uint8_t>(es.valueStack[es.bp + inst.op2]);
            std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint8_t));
            break;
        }
        case IR::coreOpcodes::store_i16: // dstPtrRg, srcRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint16_t) || valOffset > memSize - sizeof(uint16_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint16_t val = static_cast<uint16_t>(es.valueStack[es.bp + inst.op2]);
            std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint16_t));
            break;
        }
        case IR::coreOpcodes::store_i32: // dstPtrRg, srcRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint32_t) || valOffset > memSize - sizeof(uint32_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint32_t val = static_cast<uint32_t>(es.valueStack[es.bp + inst.op2]);
            std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint32_t));
            break;
        }
        case IR::coreOpcodes::store_i64: // dstPtrRg, srcRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(uint64_t) || valOffset > memSize - sizeof(uint64_t)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint64_t val = es.valueStack[es.bp + inst.op2];
            std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(uint64_t));
            break;
        }
        case IR::coreOpcodes::store_f32: // dstPtrRg, srcRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(float) || valOffset > memSize - sizeof(float)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            double doubleVal = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            float val = static_cast<float>(doubleVal);

            std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(float));
            break;
        }
        case IR::coreOpcodes::store_f64: // dstPtrRg, srcRg, offsetRg
        {
            uint64_t fatPtr = es.valueStack[es.bp + inst.op1];
            uint32_t memSize = fatPtr >> 32;
            uint32_t memOffset = fatPtr & 0xFFFFFFFF;
            uint32_t valOffset = es.valueStack[es.bp + inst.op3];

            if (memSize < sizeof(double) || valOffset > memSize - sizeof(double)) [[unlikely]]
            {
                handleOutOfBounds();
                break;
            }

            uint64_t val = es.valueStack[es.bp + inst.op2];
            std::memcpy(&es.memoryArena[memOffset + valOffset], &val, sizeof(double));
            break;
        }
        case IR::coreOpcodes::s_addr:
        case IR::coreOpcodes::alloc:
        case IR::coreOpcodes::free:
            break;
        case IR::coreOpcodes::memcpy:
        case IR::coreOpcodes::submem:
            break;
        case IR::coreOpcodes::call: // funcID | firstRg | -  
            break;
        case IR::coreOpcodes::call_cap: // capID | funcID | firstRg 
            break;
        case IR::coreOpcodes::call_lib: // libID | funcID | firstRg  
            break;
        case IR::coreOpcodes::ret:
            break;

            // int ALU
        case IR::coreOpcodes::add_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = val1 + val2;
            break;
        }
        case IR::coreOpcodes::sub_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = val1 - val2;
            break;
        }
        case IR::coreOpcodes::mul_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = val1 * val2;
            break;
        }
        case IR::coreOpcodes::div_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
            auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);

            if (val2 == 0) [[unlikely]]
            {
                handleZeroDivision();
                break;
            }

            if (val1 == std::numeric_limits<int64_t>::min() && val2 == -1) [[unlikely]]
            {
                handleOverflow();
                break;
            }

            es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 / val2);
            break;
        }
        case IR::coreOpcodes::mod_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
            auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);

            if (val2 == 0) [[unlikely]]
            {
                handleZeroDivision();
                break;
            }

            if (val1 == std::numeric_limits<int64_t>::min() && val2 == -1) [[unlikely]]
            {
                es.valueStack[es.bp + inst.op1] = 0;
                break;
            }

            es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 % val2);
            break;
        }
        case IR::coreOpcodes::add_f: // dstRg | src1Rg | src2Rg
        {
            auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 + val2);
            break;
        }
        case IR::coreOpcodes::sub_f: // dstRg | src1Rg | src2Rg
        {
            auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 - val2);
            break;
        }
        case IR::coreOpcodes::mul_f: // dstRg | src1Rg | src2Rg
        {
            auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 * val2);
            break;
        }
        case IR::coreOpcodes::div_f: // dstRg | src1Rg | src2Rg
        {
            auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);

            if (val2 == 0.0) [[unlikely]]
            {
                handleZeroDivision();
                break;
            }

            es.valueStack[es.bp + inst.op1] = std::bit_cast<uint64_t>(val1 / val2);
            break;
        }
        case IR::coreOpcodes::and_b: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = (val1 & val2);
            break;
        }
        case IR::coreOpcodes::or_b: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = (val1 | val2);
            break;
        }
        case IR::coreOpcodes::xor_b: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = (val1 ^ val2);
            break;
        }
        case IR::coreOpcodes::not_b: // dstRg | srcRg  | _ 
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            es.valueStack[es.bp + inst.op1] = !(val1);
            break;
        }
        case IR::coreOpcodes::shl_b: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = (val1 << (val2 & 0x3F)); // bounds check
            break;
        }
        case IR::coreOpcodes::shr_b: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = (val1 >> val2);
            break;
        }
        case IR::coreOpcodes::cmp_eq_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = (val1 == val2);
            break;
        }
        case IR::coreOpcodes::cmp_ne_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = es.valueStack[es.bp + inst.op2];
            auto val2 = es.valueStack[es.bp + inst.op3];
            es.valueStack[es.bp + inst.op1] = (val1 != val2);
            break;
        }
        case IR::coreOpcodes::cmp_lt_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
            auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 < val2);
            break;
        }
        case IR::coreOpcodes::cmp_gt_i: // dstRg | src1Rg | src2Rg
        {
            auto val1 = static_cast<int64_t>(es.valueStack[es.bp + inst.op2]);
            auto val2 = static_cast<int64_t>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = static_cast<uint64_t>(val1 > val2);
            break;
        }
        case IR::coreOpcodes::cmp_eq_f: //  dstRg | src1Rg | src2Rg
        {
            auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = (val1 == val2);
            break;
        }
        case IR::coreOpcodes::cmp_lt_f: //  dstRg | src1Rg | src2Rg
        {
            auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = (val1 < val2);
            break;
        }
        case IR::coreOpcodes::cmp_gt_f: //  dstRg | src1Rg | src2Rg
        {
            auto val1 = std::bit_cast<double>(es.valueStack[es.bp + inst.op2]);
            auto val2 = std::bit_cast<double>(es.valueStack[es.bp + inst.op3]);
            es.valueStack[es.bp + inst.op1] = (val1 > val2);
            break;
        }
        // EXTENSION OPS
        case IR::coreOpcodes::now_monotonic:
        case IR::coreOpcodes::now_wallclock:
        case IR::coreOpcodes::vsetvl:
        case IR::coreOpcodes::vload:
        case IR::coreOpcodes::vstore:
        case IR::coreOpcodes::vgather:
        case IR::coreOpcodes::vscatter:
        case IR::coreOpcodes::vbroadcast_s:
        case IR::coreOpcodes::vadd_i:
        case IR::coreOpcodes::vsub_i:
        case IR::coreOpcodes::vmul_i:
        case IR::coreOpcodes::vdiv_i:
        case IR::coreOpcodes::vmod_i:
        case IR::coreOpcodes::vmin_i:
        case IR::coreOpcodes::vmax_i:
        case IR::coreOpcodes::vabs_i:
        case IR::coreOpcodes::vadd_vs_i:
        case IR::coreOpcodes::vsub_vs_i:
        case IR::coreOpcodes::vmul_vs_i:
        case IR::coreOpcodes::vdiv_vs_i:
        case IR::coreOpcodes::vadd_f:
        case IR::coreOpcodes::vsub_f:
        case IR::coreOpcodes::vmul_f:
        case IR::coreOpcodes::vdiv_f:
        case IR::coreOpcodes::vmin_f:
        case IR::coreOpcodes::vmax_f:
        case IR::coreOpcodes::vabs_f:
        case IR::coreOpcodes::vsqrt_f:
        case IR::coreOpcodes::vfma_f:
        case IR::coreOpcodes::vfms_f:
        case IR::coreOpcodes::vadd_vs_f:
        case IR::coreOpcodes::vmul_vs_f:
        case IR::coreOpcodes::vmul_vs_f_i:
        case IR::coreOpcodes::vand_b:
        case IR::coreOpcodes::vor_b:
        case IR::coreOpcodes::vxor_b:
        case IR::coreOpcodes::vnot_b:
        case IR::coreOpcodes::vshl_i:
        case IR::coreOpcodes::vshr_i:
        case IR::coreOpcodes::vsar_i:
        case IR::coreOpcodes::vshl_vs_i:
        case IR::coreOpcodes::vcmp_eq_i:
        case IR::coreOpcodes::vcmp_gt_i:
        case IR::coreOpcodes::vcmp_lt_i:
        case IR::coreOpcodes::vcmp_eq_f:
        case IR::coreOpcodes::vcmp_gt_f:
        case IR::coreOpcodes::vcmp_lt_f:
        case IR::coreOpcodes::vblend_m:
        case IR::coreOpcodes::vload_m:
        case IR::coreOpcodes::vstore_m:
        case IR::coreOpcodes::vshuffle:
        case IR::coreOpcodes::vpack:
        case IR::coreOpcodes::vunpack:
        case IR::coreOpcodes::vreduce_add_i:
        case IR::coreOpcodes::vreduce_mul_i:
        case IR::coreOpcodes::vreduce_add_f:
        case IR::coreOpcodes::vreduce_max_f:
            handleNotImplementedYet();
            break;
        }
    }
    return 0;
}