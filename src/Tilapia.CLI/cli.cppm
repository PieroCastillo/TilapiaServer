/*
Created by @PieroCastillo on 2026-06-22
*/
module;
#include "common.hpp"
#include <filesystem>
#include <functional>
#include <string>
#include <print>
#include <tuple>
#include <unordered_map>

export module tilapia.cli;
import tilapia.platform;
import tilapia.terminalutils;

export namespace Tilapia::CLI
{
    void handleHelp()
    {
        auto actionDescs = std::vector{
            std::make_tuple("initd", "", "Starts daemon."),
            std::make_tuple("stopd", "[--force]", "Stops daemon."),
            std::make_tuple("start", "file.tir [-c configFile]", "Starts a runtime instance."),
            std::make_tuple("list", "", "Lists all runtime instances."),
            std::make_tuple("stop", "(ID|instanceName) [--force]", "Stop a runtime instance by ID or instance name."),
        };

        /* output */
        std::println("{}{}Tilapia Server CLI v0.1{}", TextStyle::Bold, TextStyle::Green, TextStyle::Reset);

        for (const auto& [act, params, desc] : actionDescs)
        {
            std::println("{}{}{} {} : {}", TextStyle::Bold, act, TextStyle::Reset, params, desc);
        }
    }

    void handleStartd()
    {
        std::filesystem::path daemonPath = "Tilapia.Daemon.exe";
        std::vector<std::string> argsd = { "arg0" };
        auto daemon = Tilapia::Platform::RunProcess(daemonPath, argsd, true);
        // Tilapia::Platform::DetachProcess(daemon);
    }

    void handleStopd(bool force)
    {
        if(force)
            Tilapia::Platform::KillProcessByName("tilapiad");
    }

    void handleList(Tilapia::Platform::Socket clientSck)
    {

    }

    void handleStart(Tilapia::Platform::Socket clientSck, std::filesystem::path runtimePath, std::optional<std::filesystem::path> configFilePath)
    {

    }

    void handleStop(Tilapia::Platform::Socket clientSck, uint32_t instanceID, std::optional<std::string> instanceName)
    {
        // use instanceID
        if(!instanceName)
        {

        }
        // use instance name
    }
};