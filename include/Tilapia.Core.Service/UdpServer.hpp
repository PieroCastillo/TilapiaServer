/*
Created by @PieroCastillo on 2026-04-19
*/
#ifndef TILAPIA_CORE_SERVICE_UDP_SERVER_HPP
#define TILAPIA_CORE_SERVICE_UDP_SERVER_HPP

namespace Tilapia::Service
{
    struct IncomingPacket
    {
        uint32_t connectionId;
        std::span<const std::byte> payload;
    };

    struct UdpServerDesc
    {
        uint16_t port;
        uint64_t packetSize;
        uint64_t packetCount;
        std::move_only_function<void(std::span<const IncomingPacket> packets)> processPacketsFn;
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
        auto MainLoop();
    };
};
#endif // TILAPIA_CORE_SERVICE_UDP_SERVER_HPP