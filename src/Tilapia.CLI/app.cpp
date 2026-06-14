#include "common.hpp"

import std;
import tilapia.platform;
import tilapia.cli;

const std::string daemonSocketName = "tilapia_daemon.sock";
Tilapia::Platform::Socket clientSocket;

int main(int argc, char** argv)
{
    std::println("Tilapia CLI v0.1");
    std::filesystem::path daemonPath = "Tilapia.Daemon.exe";
    std::vector<std::string> args = { "arg0" };
    auto daemon = Tilapia::Platform::RunProcess(daemonPath, args);
    Tilapia::Platform::DetachProcess(daemon);

    Tilapia::Platform::InitSocketsAPI();
    clientSocket = Tilapia::Platform::Connect(Tilapia::Platform::BuildSocketPath(daemonSocketName));

    while (true)
    {
        // uint32_t msgIn, msgOut = 20;
        // Tilapia::Platform::Send(clientSocket, &msgOut, 1);
        // Tilapia::Platform::Recv(clientSocket, &msgIn, 1, false);
        // std::println("value: {}", msgIn);

        std::string input;
        std::getline(std::cin, input);
        auto payloadSize = input.size();

        Tilapia::Platform::Send(clientSocket, std::span(reinterpret_cast<uint8_t*>(&payloadSize), sizeof(payloadSize)));
        Tilapia::Platform::Send(clientSocket, std::span(reinterpret_cast<uint8_t*>(input.data()), payloadSize));
    }

    Tilapia::Platform::Close(clientSocket);
    Tilapia::Platform::CleanupSocketsAPI();
    return 0;
}