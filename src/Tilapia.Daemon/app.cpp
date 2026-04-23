#include <cstdint>

#include "common.hpp"
#include "UdpServer.hpp"

/*
base:
UDP
QUIC
HTTP/3
WebTransport
compatibility:
TLS 1.3
HTTP/2
WebSockets
SSE
gRPC
*/

std::unique_ptr<Tilapia::Daemon::UdpServer> server;

int main(int argc, char** argv)
{
    // NOW, WINDOWS ONLY (next step, imlp udp for win/linux)
    std::println("Tilapia Core Service v0.1");
    
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