#include "common.hpp"

import std;
import tilapia.platform;
import tilapia.cli;

int main(int argc, char** argv)
{
    std::println("Tilapia CLI v0.1");
    std::filesystem::path daemonPath = "Tilapia.Daemon.exe";
    std::vector<std::string> args = { "arg0" };
    auto daemon = Tilapia::Platform::RunProcess(daemonPath, args);
    Tilapia::Platform::DetachProcess(daemon);
    return 0;
}