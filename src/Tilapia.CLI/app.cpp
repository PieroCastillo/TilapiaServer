#include "common.hpp"

import std;
import tilapia.cli;
import tilapia.platform;

const std::string daemonSocketName = "tilapia_daemon.sock";
Tilapia::Platform::Socket clientSocket;

void connect()
{
    Tilapia::Platform::InitSocketsAPI();
    clientSocket = Tilapia::Platform::Connect(Tilapia::Platform::BuildSocketPath(daemonSocketName));
}

void close()
{
    Tilapia::Platform::Close(clientSocket);
    Tilapia::Platform::CleanupSocketsAPI();
}

int main(int argc, char** argv)
{
    auto args = std::vector<std::string>(argv, argv + argc);

    if (argc <= 1)
    {
        std::println("No action defined.");
        return 0;
    }

    /* args compare and select action */
    auto action = args[1];
    if (action == "help")
    {
        Tilapia::CLI::handleHelp();
    }
    else if (action == "startd")
    {
        Tilapia::CLI::handleStartd();
    }
    else if (action == "stopd")
    {
        bool forced = args.size() >= 3 && args[2] == "--force";
        Tilapia::CLI::handleStopd(forced);
    }
    else if (action == "start")
    {
        connect();
        // auto rtPath = std::filesystem::path(args[2]);
        close();
    }
    else if (action == "list")
    {
        connect();
        Tilapia::CLI::handleList(clientSocket);
        close();
    }
    else if (action == "stop")
    {
        connect();

        close();
    }
    else
    {
        std::println("Invalid Action: {}", action);
    }
    return 0;

    // while (true)
    // {
        // uint32_t msgIn, msgOut = 20;
        // Tilapia::Platform::Send(clientSocket, &msgOut, 1);
        // Tilapia::Platform::Recv(clientSocket, &msgIn, 1, false);
        // std::println("value: {}", msgIn);

        // std::string input;
        // std::getline(std::cin, input);
        // auto payloadSize = input.size();

        // Tilapia::Platform::Send(clientSocket, std::span(reinterpret_cast<uint8_t*>(&payloadSize), sizeof(uint32_t)));
        // Tilapia::Platform::Send(clientSocket, std::span(reinterpret_cast<uint8_t*>(input.data()), payloadSize));
    //}

    return 0;
}