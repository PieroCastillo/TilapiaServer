/*
Created by @PieroCastillo on 2026-06-10
*/
module;

#include "common.hpp"
#include <cstdint>
#include <functional>
#include <span>
#include <thread>
#include <vector>

export module tilapia.daemon.clientpool;
import tilapia.platform;

export namespace Tilapia::Daemon
{
    enum class ControlInstruction
    {
        // runtime lifecycle
        Start,
        Pause,
        Shutdown,
        // file I/O
        OpenFile,
        CloseFile,
        // network I/O
        OpenConnection,
        CloseConnection,
    };

    struct ControlMessage
    {

    };

    using Client = uint64_t;

    class ClientPool
    {
        private:
        // access data
        std::vector<Tilapia::Platform::Socket> runtimeClients;
        std::vector<uint32_t> generations;
        // resources
        std::vector<std::jthread> clientThreads;
        std::vector<Tilapia::Platform::SharedMemory> sharedMemories;
        std::vector<Tilapia::Platform::Process> runtimeIntances;
        public:
        void SendControl(Client client, ControlMessage msg)
        {

        }

        void RecvControl(Client client, ControlMessage msg)
        {

        }
    };
}