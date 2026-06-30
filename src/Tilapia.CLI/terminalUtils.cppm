/*
Created by @PieroCastillo on 2026-06-22
*/
module;

#include "common.hpp"
#include <functional>
#include <string>
#include <print>
#include <unordered_map>

export module tilapia.terminalutils;

export namespace Tilapia::CLI::TextStyle
{
    constexpr auto Reset = "\033[0m";

    constexpr auto Black = "\033[30m";
    constexpr auto Red = "\033[31m";
    constexpr auto Green = "\033[32m";
    constexpr auto Yellow = "\033[33m";
    constexpr auto Blue = "\033[34m";
    constexpr auto Magenta = "\033[35m";
    constexpr auto Cyan = "\033[36m";
    constexpr auto White = "\033[37m";

    constexpr auto Gray = "\033[90m";
    constexpr auto BrightRed = "\033[91m";
    constexpr auto BrightGreen = "\033[92m";
    constexpr auto BrightYellow = "\033[93m";
    constexpr auto BrightBlue = "\033[94m";
    constexpr auto BrightMagenta = "\033[95m";
    constexpr auto BrightCyan = "\033[96m";
    constexpr auto BrightWhite = "\033[97m";

    constexpr auto Bold = "\033[1m";
    constexpr auto Italic = "\033[3m";
    constexpr auto Underline = "\033[4m";
};