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

export module tilapia.daemon.runtimepool;
import tilapia.platform;

export namespace Tilapia::Daemon
{
    using Runtime = uint64_t;

    class RuntimePool
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