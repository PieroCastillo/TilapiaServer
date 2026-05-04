/*
Created by @PieroCastillo on 2026-05-04
*/
module;

#include <cstdint>
#include <filesystem>
#include <span>
#include <string>

export module tilapia.platform:process;

export namespace Tilapia::Platform
{
    struct Process
    {
        uint32_t pid;
        uint64_t handle;
    };
    void EnsureSingle();
    auto RunProcess(const std::filesystem::path& appPath, std::span<const std::string> args) -> Process;
    void KillProcess(const Process& process);
    void DetachProcess(const Process& process);
}