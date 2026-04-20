#include "common.hpp"

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
    scheduler.add(executionUnit(execBinary)); // starts caps
    while()
    {
    
    }
    */

    return 0;
}