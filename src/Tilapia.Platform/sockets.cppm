/*
Created by @PieroCastillo on 2026-05-06
*/
module;

#include <chrono>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <span>
#include <tuple>

export module tilapia.platform:sockets;

export namespace Tilapia::Platform
{
    using Socket = int64_t;

    void InitSocketsAPI();
    void CleanupSocketsAPI();
    auto IsValid(Socket socket) -> bool;

    auto ConfigureServer(const std::string& path, uint32_t queueSize) -> Socket;
    auto Accept(Socket server) -> Socket;
    void Close(Socket socket);

    auto Connect(const std::string& path) -> Socket;

    void Recv(Socket socket, std::span<uint8_t> data);
    void Send(Socket socket, std::span<const uint8_t> data);

    auto BuildSocketPath(const std::string& path) -> std::string;
    void Poll(std::span<const Socket> sockets, std::chrono::milliseconds timeout, std::move_only_function<void(Socket)> callback);
}