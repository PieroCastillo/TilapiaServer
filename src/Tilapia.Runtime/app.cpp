#include <stdlib.h>

#include "common.hpp"
#include "ir.hpp"

using namespace TilapiaServer::Runtime;
using namespace TilapiaServer::Runtime::IR;

std::string fakeAsm = 
R"(executionModel plugin
entryPoint main
cap core.print
.ro
%1 = "hola tilapia IR"
.text
fn main():
core.print %1
)";

int main(int argc, char **argv) {
    std::println("Tilapia Runtime v0.1");

    std::string asmPath;

    if(!(std::cin >> asmPath))
    {
        std::println("Invalid Input");
    }


    /*
    execBinary = load(asmPath); // converts raw data to spec-valid IR Assembly
    validate(execBinary); // check caps
    while()
    */

    std::vector<instruction> opts;
    bool shouldStop = false;
    auto stackSize = 4 * 1024; // 4KB
    const auto stackPtr = malloc(stackSize);
    auto stackOffset = 0;

    while(!shouldStop)
    {
    
    }
    free(stackPtr);

    return 0;
}