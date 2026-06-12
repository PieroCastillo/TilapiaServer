#include "common.hpp"

import std;
import tilapia.daemon.udpserver;
import tilapia.platform;

const std::string daemonSocketName = "tilapia_daemon.sock";
Tilapia::Platform::Socket serverSocket;

struct CLICollection
{
    std::vector<Tilapia::Platform::Socket> cliSockets;
    std::vector<uint32_t> generations;
    std::vector<uint32_t> freeList;
};

std::unique_ptr<Tilapia::Daemon::UdpServer> server;

int main(int argc, char** argv)
{
    auto args = std::vector<std::string>(argv, argv + argc);
    // NOW, WINDOWS ONLY (next step, imlp udp for win/linux)
    std::println("Tilapia Daemon v0.1");
    // print args
    std::println("args:");
    for (const auto& arg : args)
        std::print("  > {} ", arg);
    std::println();

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

    auto clientSck = Tilapia::Platform::Accept(serverSocket);
    if (!Tilapia::Platform::IsValid(clientSck))
    {
        return 0;
    }

    // control loop
    while (true)
    {
        // Tilapia::Platform::Poll()
/*      for(client in incomming clients)
        {
            auto client = accept(serverSocket);
            clients.add(client);
        }

        for( client in sendingClientsOnly(clients))
        {
            auto msg = recv(client);
            // do
        }

        for( rtClient in sendingClientsOnly(runtimeClients))
        {
            auto msg = recv(rtClient);
        }
*/  
        // uint32_t value;
        // Tilapia::Platform::Recv<uint32_t>(clientSck, &value, 1, true);
        // std::println("value: {}", value);
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