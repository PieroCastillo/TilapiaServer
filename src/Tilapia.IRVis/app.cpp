#include "common.hpp"
#include <cstdint>

import std;
import tilapia.dummy;
import tilapia.irlib;

using namespace Tilapia::IRLib;

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
    auto args = std::vector<std::string>(argv, argv + argc);
    std::println("Tilapia IR Visualizer v0.1");

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

    auto exeRes = loadBin(asmBytes, binDesc.value());
    if (!exeRes)
    {
        std::print("Internal File Error");
        return -1;
    }

    binary executable = exeRes.value();

    return 0;
}