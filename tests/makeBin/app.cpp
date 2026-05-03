#include <cstdint>

import std;
import tilapia.irlib;

using namespace Tilapia::IRLib;

bool saveFile(const std::filesystem::path& path, std::span<const uint8_t> data)
{
    if (path.has_parent_path())
    {
        std::filesystem::create_directories(path.parent_path());
    }

    std::ofstream file(path, std::ios::binary);
    if (!file) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));

    return file.good();
}

int main(int argc, char** argv)
{
    const std::filesystem::path asmPath = "./gen/helloWorldTest.tir";

    binary bin = {};
    bin.header.magic = 0x74694952; // "tiIR"
    bin.header.versionMajor = 1;
    bin.header.versionMinor = 0;
    bin.header.flags = 0;
    bin.header.entrypointOffset = 0;
    bin.header.executableName = "test exec";

    bin.capabilities.push_back({ coreCaps::print, 1, 0, 0 });
    bin.entrypoints.push_back({ entrypointType::executable, 0, 0 });
    bin.functions.push_back({ 0, 3, 0, 0 });

    auto helloWorldStr = std::string("hello world");
    bin.readOnlyData.push_back({ (uint32_t)helloWorldStr.size(), 0, 0 });
    bin.readOnlyDataPool.insert(bin.readOnlyDataPool.end(), helloWorldStr.begin(), helloWorldStr.end());
    bin.readOnlyDataSize = (uint32_t)bin.readOnlyDataPool.size();

    uint32_t rg0 = 0;
    bin.instructions.push_back({ (uint32_t)coreOpcodes::li64, rg0, (uint32_t)helloWorldStr.size(), 0 }); // hi: size, lo: offset
    bin.instructions.push_back({ (uint32_t)coreOpcodes::call_cap, (uint32_t)coreCaps::print, (uint32_t)coreCalls::print_str, rg0 });
    bin.instructions.push_back({ (uint32_t)coreOpcodes::ret });

    auto asmBytes = makeBinary(bin);

    if (!saveFile(asmPath, asmBytes))
    {
        std::println("test file could not be saved");
        return 0;
    }
    return 0;
};