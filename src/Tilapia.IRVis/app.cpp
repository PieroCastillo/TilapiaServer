#include "common.hpp"
#include <cstdint>

import std;
import tilapia.irlib;
import tilapia.printInst;

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
    auto binDescRes = loadDesc(asmBytes);
    if (!binDescRes)
    {
        std::print("File Description Error");
        return -1;
    }
    auto binDesc = binDescRes.value();

    // std::println("DESCRIPTION (FIRST 128 BYTES)");
    // std::println("executableNameOffset   : {} ", binDesc.executableNameOffset);
    // std::println("capabilitiesOffset     : {} ", binDesc.capabilitiesOffset);
    // std::println("typesOffset            : {} ", binDesc.typesOffset);
    // std::println("typesPoolOffset        : {} ", binDesc.typesPoolOffset);
    // std::println("symbolsOffset          : {} ", binDesc.symbolsOffset);
    // std::println("dynamicLibsOffset      : {} ", binDesc.dynamicLibsOffset);
    // std::println("entrypointsOffset      : {} ", binDesc.entrypointsOffset);
    // std::println("functionsOffset        : {} ", binDesc.functionsOffset);
    // std::println("roDataOffset           : {} ", binDesc.roDataOffset);
    // std::println("roDataPoolOffset       : {} ", binDesc.roDataPoolOffset);
    // std::println("rwDataOffset           : {} ", binDesc.rwDataOffset);
    // std::println("rwDataPoolOffset       : {} ", binDesc.rwDataPoolOffset);
    // std::println("Instructions Offset    : {} ", binDesc.instructionsOffset);

    // std::println("executableNameCharCount : {} ", binDesc.executableNameCharCount);
    // std::println("capabilitiesCount      : {} ", binDesc.capabilitiesCount);
    // std::println("typesCount             : {} ", binDesc.typesCount);
    // std::println("symbolsCount           : {} ", binDesc.symbolsCount);
    // std::println("dynamicLibsCount       : {} ", binDesc.dynamicLibsCount);
    // std::println("entrypointsCount       : {} ", binDesc.entrypointsCount);
    // std::println("functionsCount         : {} ", binDesc.functionsCount);
    // std::println("roDataCount            : {} ", binDesc.roDataCount);
    // std::println("rwDataCount            : {} ", binDesc.rwDataCount);
    // std::println("Instructions Count     : {} ", binDesc.instructionsCount);

    // std::println("typesPoolSize          : {} ", binDesc.typesPoolSize);
    // std::println("roDataPoolSize         : {} ", binDesc.roDataPoolSize);
    // std::println("rwDataPoolSize         : {} ", binDesc.rwDataPoolSize);
    // std::println("uninitializedDataSize  : {} ", binDesc.uninitializedDataSize);

    auto exeRes = loadBin(asmBytes, binDesc);
    if (!exeRes)
    {
        std::print("Internal File Error");
        return -1;
    }

    binary bin = exeRes.value();
    std::println("HEADER");
    std::println("Magic Number       : {:#010x}", bin.header.magic);
    std::println("Version Major      : {}", bin.header.versionMajor);
    std::println("Version Minor      : {}", bin.header.versionMinor);
    std::println("Flags              : {}", bin.header.flags);
    std::println("Entry Point Offset : {}", bin.header.entrypointOffset);
    std::println("Executable Name    : {}", bin.header.executableName);
    std::println("RO Size            : {}", bin.readOnlyDataSize);
    std::println("RW Size            : {}", bin.readWriteDataSize);
    std::println("BSS Size           : {}", bin.uninitializedDataSize);

    std::println("CAPABILITIES");
    for (size_t i = 0; i < bin.capabilities.size(); ++i)
    {
        const auto& cap = bin.capabilities[i];

        std::println(
            "[{}] {:<16} v{}.{} flags=0x{:08X}",
            i,
            to_string(cap.capId),
            cap.versionMajor,
            cap.versionMinor,
            cap.flags
        );
    }

    std::println("TYPES");
    for (size_t i = 0; i < bin.types.size(); ++i)
    {
        const auto& typ = bin.types[i];

        std::println(
            "[{}] offset={} subtypeCount={}",
            i,
            typ.offset,
            typ.subtypeCount
        );
    }

    std::println("SYMBOLS");
    for (size_t i = 0; i < bin.symbols.size(); ++i)
    {
        const auto& sym = bin.symbols[i];

        std::println(
            "[{}] {:<12} offset={} size={} flags=0x{:08X}",
            i,
            to_string(sym.type),
            sym.offset,
            sym.size,
            sym.flags
        );
    }

    std::println("DYNAMIC LIBRARIES");
    for (size_t i = 0; i < bin.dynamicLibs.size(); ++i)
    {
        const auto& dynlib = bin.dynamicLibs[i];

        std::println(
            "[{}] version={} symbolOffset={} flags=0x{:08X}",
            i,
            dynlib.version,
            dynlib.symbolOffset,
            dynlib.flags
        );
    }

    std::println("ENTRY POINTS");
    for (size_t i = 0; i < bin.entrypoints.size(); ++i)
    {
        const auto& ep = bin.entrypoints[i];

        std::println(
            "[{}] {:<12} instructionOffset={} flags=0x{:08X}",
            i,
            to_string(ep.type),
            ep.instructionOffset,
            ep.flags
        );
    }

    std::println("FUNCTIONS");
    for (size_t i = 0; i < bin.functions.size(); ++i)
    {
        const auto& func = bin.functions[i];

        std::println(
            "[{}] start={} count={} params={} flags=0x{:04X}",
            i,
            func.startInstructionOffset,
            func.instructionCount,
            func.paramCount,
            func.flags
        );
    }

    std::println("READ ONLY DATA");
    for (size_t i = 0; i < bin.readOnlyData.size(); ++i)
    {
        const auto& rod = bin.readOnlyData[i];

        std::println(
            "[{}] size={} dataOffset={} alignment={}",
            i,
            rod.size,
            rod.dataOffset,
            rod.alignment
        );
    }

    std::println("READ WRITE DATA");
    for (size_t i = 0; i < bin.readWriteData.size(); ++i)
    {
        const auto& rwd = bin.readWriteData[i];

        std::println(
            "[{}] size={} dataOffset={} alignment={}",
            i,
            rwd.size,
            rwd.dataOffset,
            rwd.alignment
        );
    }

    std::println("INSTRUCTIONS");
    for (size_t i = 0; i < bin.instructions.size(); ++i)
    {
        printInstruction(bin.instructions[i], i);
    }

    return 0;
}