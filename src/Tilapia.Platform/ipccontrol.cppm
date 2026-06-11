/*
Created by @PieroCastillo on 2026-06-10
*/
module;

#include <chrono>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <span>
#include <tuple>

export module tilapia.platform:ipccontrol;

export namespace Tilapia::Platform::IPCControl
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
    enum class Action
    {
        RequestFile,
        RequestPort
    };

    struct ControlMessage
    {

    };
}