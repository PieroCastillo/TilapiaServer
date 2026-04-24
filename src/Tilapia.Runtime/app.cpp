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
    while()
    */

    binary executable;
    Instance executionState;

    return 0;
}