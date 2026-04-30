/*
Created by @PieroCastillo on 2026-04-19
*/
module;

#include "common.hpp"
#include <cstdint>
#include <functional>
#include <span>

export module tilapia.daemon.udpserver;

export namespace Tilapia::Daemon
{
    struct Endpoint
    {
        uint32_t ipv4;
        uint16_t port;
    };

    struct InPacket
    {
        uint32_t connectionId;
        Endpoint src;
        std::span<const std::byte> payload;
    };

    struct OutPacket
    {
        Endpoint dst;
        std::span<const std::byte> payload;
    };

    struct UdpBatch
    {
        std::span<const InPacket> incoming;
        std::span<const OutPacket> outgoing;
    };

    struct UdpServerDesc
    {
        uint16_t port;
        uint64_t packetSize;
        uint64_t packetCount;
        // uint32_t recvBatchSize = 64;
        // uint32_t sendBatchSize = 64;
        // bool enableZeroCopy = true;
        // bool busyPoll = true;
        // std::move_only_function<void(UdpBatch)> handle;
    };

    struct NetContext;
    struct UdpServerContext;

    class UdpServer
    {
    private:
        const uint16_t port;
        const uint64_t packetSize;
        const uint64_t packetCount;
        const uint64_t bufferSize;
        UdpServerContext* serverContext;
    public:
        explicit UdpServer(const UdpServerDesc& desc);
        ~UdpServer();
                
        // void Start();
        // void Stop();
        // void Poll();
        // void Send(std::span<const OutgoingPacket>);
        void Run();
    };
};