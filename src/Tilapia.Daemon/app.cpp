#include "common.hpp"
#include "malloc.h"

import std;
import tilapia.daemon.udpserver;
import tilapia.platform;

const std::string daemonSocketName = "tilapia_daemon.sock";

Tilapia::Platform::Socket serverSocket;
std::vector<Tilapia::Platform::Socket> cliSockets;
std::vector<Tilapia::Platform::Socket> runtimeSockets;

int main(int argc, char** argv)
{
    auto args = std::vector<std::string>(argv, argv + argc);
    std::println("Tilapia Daemon v0.1");

    if (!Tilapia::Platform::EnsureSingle())
    {
        std::println("Tilapia Daemon is already running");
        return 0;
    }

    // init sockets for IPC
    Tilapia::Platform::InitSocketsAPI();
    serverSocket = Tilapia::Platform::ConfigureServer(Tilapia::Platform::BuildSocketPath(daemonSocketName), 10);

    if (!Tilapia::Platform::IsValid(serverSocket))
    {
        std::println("bad config");
        return 0;
    }

    // control loop
    while (true)
    {
        Tilapia::Platform::PollIn(
            std::span(&serverSocket, 1),
            std::chrono::milliseconds(2),
            [&](Tilapia::Platform::Socket sck) {
                auto clientSck = Tilapia::Platform::Accept(sck);
                if (!Tilapia::Platform::IsValid(clientSck))
                {
                    return;
                }
                cliSockets.push_back(clientSck);
                std::println("CLI client accepted!");
            });

        Tilapia::Platform::PollIn(
            cliSockets,
            std::chrono::milliseconds(2),
            [&](Tilapia::Platform::Socket sck) {
                uint32_t payloadSize;
                Tilapia::Platform::Recv(sck, &payloadSize, 1);
                auto payload = (char*)alloca(payloadSize);
                Tilapia::Platform::Recv(sck, std::span((uint8_t*)payload, payloadSize));
                std::println("{}", std::string(payload, payloadSize));
            }
        );

        Tilapia::Platform::PollIn(
            runtimeSockets,
            std::chrono::milliseconds(2),
            [&](Tilapia::Platform::Socket sck) {
                uint32_t msg;
                Tilapia::Platform::Recv(sck, &msg, 1);
            }
        );
    }

    Tilapia::Platform::Close(serverSocket);
    Tilapia::Platform::CleanupSocketsAPI();

    // auto mem = Tilapia::Platform::sharedAlloc(1024);
    // Tilapia::Daemon::UdpServerDesc servDesc =
    // {
    //     .port = 8888,
    //     .packetSize = 1024,
    //     .packetCount = 64,
    // };
    // server = std::make_unique<Tilapia::Daemon::UdpServer>(servDesc);
    // server->Run();

    return 0;
}