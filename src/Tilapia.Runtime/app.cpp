#include <stdlib.h>

#include "IR.hpp"
#include "Instance.hpp"
#include "common.hpp"

using namespace TilapiaServer::Runtime;
using namespace TilapiaServer::Runtime::IR;

std::string fakeAsm =
R"(executionModel plugin
entryPoint main
cap core.print
.ro
c1 string byteSize "hello tilapia IR"
.text
fn main():
push c1
call core.print
decl v1 i32
add v1 3 2
ret
c1 c2 c3 c4 // constant/ro
w1 w2 w3 w4 // rw static memory
v1 v2 v3 v4 // stack variables
)";

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
    while()0x0400IR
    */

    binary executable;
    Instance executionState;
    ConfigureInstance(&executable, &executionState, 4 * 1024 * 1024); // 4 MB arena

    auto& program = executable.instructions;
    while (executionState.isRunning)
    {
        const IR::instruction& inst = executable.instructions[executionState.ip++];
        uint32_t op = (inst.capId << 16) & inst.opCode;

        switch (static_cast<IR::coreOpcodes>(op))
        {
        case IR::coreOpcodes::nop:
            break;
        case IR::coreOpcodes::push_var:
        case IR::coreOpcodes::push_imm_i32:
        case IR::coreOpcodes::push_const:
        case IR::coreOpcodes::pop_var:
        case IR::coreOpcodes::call_local:
        case IR::coreOpcodes::call_cap:
        case IR::coreOpcodes::call_ext:
        case IR::coreOpcodes::add_i:
        case IR::coreOpcodes::sub_i:
        case IR::coreOpcodes::mul_i:
        case IR::coreOpcodes::div_i:
        case IR::coreOpcodes::mod_i:
        case IR::coreOpcodes::add_f:
        case IR::coreOpcodes::sub_f:
        case IR::coreOpcodes::mul_f:
        case IR::coreOpcodes::div_f:
        case IR::coreOpcodes::and_b:
        case IR::coreOpcodes::or_b:
        case IR::coreOpcodes::xor_b:
        case IR::coreOpcodes::not_b:
        case IR::coreOpcodes::shl_b:
        case IR::coreOpcodes::shr_b:
        case IR::coreOpcodes::cmp_eq_i:
        case IR::coreOpcodes::cmp_ne_i:
        case IR::coreOpcodes::cmp_lt_i:
        case IR::coreOpcodes::cmp_gt_i:
        case IR::coreOpcodes::cmp_eq_f:
        case IR::coreOpcodes::cmp_lt_f:
        case IR::coreOpcodes::cmp_gt_f:
        case IR::coreOpcodes::load_u8:
        case IR::coreOpcodes::load_i32:
        case IR::coreOpcodes::load_i64:
        case IR::coreOpcodes::load_f64:
        case IR::coreOpcodes::store_u8:
        case IR::coreOpcodes::store_i32:
        case IR::coreOpcodes::store_i64:
        case IR::coreOpcodes::store_f64:
        case IR::coreOpcodes::memcpy:
        case IR::coreOpcodes::memmove:
        case IR::coreOpcodes::memset:
        case IR::coreOpcodes::alloc:
        case IR::coreOpcodes::free:
        case IR::coreOpcodes::protect:
            break;
            // EXTENSION OPS
        case IR::coreOpcodes::now_monotonic:
        case IR::coreOpcodes::now_wallclock:
        case IR::coreOpcodes::vadd_i:
        case IR::coreOpcodes::vsub_i:
        case IR::coreOpcodes::vmul_i:
        case IR::coreOpcodes::vdiv_i:
        case IR::coreOpcodes::vadd_f:
        case IR::coreOpcodes::vsub_f:
        case IR::coreOpcodes::vmul_f:
        case IR::coreOpcodes::vdiv_f:
        case IR::coreOpcodes::vand_b:
        case IR::coreOpcodes::vor_b:
        case IR::coreOpcodes::vxor_b:
        case IR::coreOpcodes::vload:
        case IR::coreOpcodes::vstore:
        case IR::coreOpcodes::vshuffle:
        case IR::coreOpcodes::vreduce_add_i:
        case IR::coreOpcodes::vreduce_add_f:
            break;
        }
    }
    return 0;
}