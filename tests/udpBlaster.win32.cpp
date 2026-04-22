#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <iostream>
#include <print>

#pragma comment(lib, "ws2_32.lib")

constexpr int PACKET_SIZE = 512;
constexpr int THREADS = 4;

std::atomic<uint64_t> packetsSent{0};
std::atomic<uint64_t> bytesSent{0};

void senderThread(sockaddr_in target)
{
    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    char buffer[PACKET_SIZE] = {};

    while (true)
    {
        int sent = sendto(
            s,
            buffer,
            PACKET_SIZE,
            0,
            (sockaddr*)&target,
            sizeof(target)
        );

        if (sent > 0)
        {
            packetsSent++;
            bytesSent += sent;
        }
    }
}

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    sockaddr_in target{};
    target.sin_family = AF_INET;
    target.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &target.sin_addr);

    std::vector<std::thread> threads;

    for (int i = 0; i < THREADS; i++)
    {
        threads.emplace_back(senderThread, target);
    }

    auto last = std::chrono::steady_clock::now();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        uint64_t p = packetsSent.exchange(0);
        uint64_t b = bytesSent.exchange(0);
        std::println("[CLIENT] packets/s: {} bytes/s: {} MB/s: {}", p, b, b / 1024.0 / 1024.0);
    }

    for (auto& t : threads)
        t.join();

    WSACleanup();
}