/*
Created by @PieroCastillo on 2026-06-10
*/
module;

#include <atomic>
#include <cstdint>
#include <string>
#include <string_view>
#include <span>

export module tilapia.protocol:userqueues;

export namespace Tilapia::Protocol
{
    /*
    cli -> daemon
    init [-t threads]
    exit
    runtime:
        run executable.tir -c config -n "name"
        pause -n name
        shutdown  -n name
    statistics

    daemon -> cli
    output text

    daemon -> runtime
    run runtime
    pause runtime
    shutdown runtime
    send input text
    packets block

    runtime -> daemon
    request file
    request udp/quic/http3 connection
    request input text
    send output text
    */

    struct CompletionPacket
    {
        uint32_t opcode;
        uint32_t flags;
        uint32_t payloadOffset;
        uint32_t payloadSize;
        uint64_t requestId;
    };

    struct ReceivePacket
    {
        uint64_t requestId;
        int32_t status;
        uint32_t resultOffset;
        uint32_t resultSize;
    };
}