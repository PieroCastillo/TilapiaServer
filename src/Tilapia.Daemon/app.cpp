#include "common.hpp"

import std;
import tilapia.daemon.udpserver;
import tilapia.platform;

/*
base:
UDP
QUIC
HTTP/3
WebTransportv
compatibility:
TLS 1.3
HTTP/2
WebSockets
SSE
gRPC
run daemon
*/

std::unique_ptr<Tilapia::Daemon::UdpServer> server;

int main(int argc, char** argv)
{
    auto args = std::vector<std::string>(argv, argv + argc);
    // NOW, WINDOWS ONLY (next step, imlp udp for win/linux)
    std::println("Tilapia Daemon v0.1");
    // print args
    std::println("args:");
    for(const auto& arg : args)
        std::print("  > {} ", arg);
    std::println();

    if(!Tilapia::Platform::EnsureSingle())
    {
        std::println("Tilapia Daemon is already running");
        return 0;
    }

    auto mem = Tilapia::Platform::sharedAlloc(1024);

    Tilapia::Daemon::UdpServerDesc servDesc =
    {
        .port = 8888,
        .packetSize = 1024,
        .packetCount = 64,
    };
    server = std::make_unique<Tilapia::Daemon::UdpServer>(servDesc);
    server->Run();

    return 0;
}