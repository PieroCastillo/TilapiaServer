#include "common.hpp"
#include <cstdint>

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

int main(int argc, char** argv)
{
    // NOW, WINDOWS ONLY (next step, imlp udp for win/linux)
    std::println("Tilapia Core Service v0.1");
    netInit();

    uint16_t port = 8888;
    uint32_t size = 1024;

    sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };
    server.sin_addr.s_addr = INADDR_ANY;
    auto s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bind(s, (struct sockaddr*)&server, sizeof(server));

    auto recvPackets = std::jthread([&](std::stop_token stopToken) {
        sockaddr_in client;
        int client_len = sizeof(client);
        std::vector<uint8_t> buf(size);
        std::println("Waiting for datagrams...");

        while (!stopToken.stop_requested())
        {
            auto recv_len = recvfrom(s, (char*)buf.data(), size, 0, (struct sockaddr*)&client, &client_len);

            if (recv_len != SOCKET_ERROR) {
                std::println("Received: {}", std::string_view((char*)buf.data(), recv_len));
            }
        }
        std::println("worker finished");
        });

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    netCloseSocket(s);
    netCleanup();
    return 0;
}