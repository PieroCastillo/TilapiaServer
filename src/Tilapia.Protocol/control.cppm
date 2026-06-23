/*
Created by @PieroCastillo on 2026-06-10
*/
module;

#include <atomic>
#include <cstdint>
#include <string>
#include <string_view>
#include <span>

export module tilapia.protocol:control;

export namespace Tilapia::Protocol
{   
    enum class ControlMessageType : uint32_t
    {
        List,
        StartRuntime,
        StopRuntime,
        Shutdown,
        Text,
    };

    struct ControlInputHeader
    {
        ControlMessageType type;
        uint32_t messageSize;
        uint32_t messageCount;
    };
};