#include <tuple>
#include <span>
#include <vector>

#ifdef _WIN32
#define NOMINMAX
#include <winsock2.h>
#include <afunix.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using socket_t = SOCKET;
constexpr socket_t INVALID_FD = INVALID_SOCKET;
#else

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

using socket_t = int;
constexpr socket_t INVALID_FD = -1;
#endif

import std;
import tilapia.platform;

namespace Tilapia::Platform
{
    void InitSocketsAPI()
    {
#ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
    }

    void CleanupSocketsAPI()
    {
#ifdef _WIN32
        WSACleanup();
#endif
    }

    auto IsValid(Socket socket) -> bool
    {
#ifdef _WIN32
        return (socket != INVALID_SOCKET);
#else
        return ((int)socket >= 0);
#endif
    }

    void Close(Socket s)
    {
#ifdef _WIN32
        closesocket(s);
#else
        close(s);
#endif
    }

    auto ConfigureServer(const std::string& path, uint32_t queueSize) -> Socket
    {
        int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (server_fd == -1) {
            return -1;
        }

        sockaddr_un server_addr{};
        server_addr.sun_family = AF_UNIX;
        std::strncpy(server_addr.sun_path, path.c_str(), sizeof(server_addr.sun_path) - 1);
        unlink(path.c_str());

        if (bind(server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
            return -2;
        }

        if (listen(server_fd, queueSize) == -1) {
            return -3;
        }
        return server_fd;
    }

    auto Accept(Socket server) -> Socket
    {
        int clientFd = accept(server, nullptr, nullptr);
        return clientFd;
    }

    auto Connect(const std::string& path) -> Socket
    {
        int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sock_fd == -1)
        {
            return -1;
        }

        sockaddr_un server_addr{};
        server_addr.sun_family = AF_UNIX;
        std::strncpy(server_addr.sun_path, path.c_str(), sizeof(server_addr.sun_path) - 1);

        if (connect(sock_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1)
        {
            Close(sock_fd);
            return -1;
        }

        return sock_fd;
    }

    void Recv(Socket socket, std::span<uint8_t> data, bool waitAll)
    {
        if(waitAll)
        {
        #ifdef _WIN32
                recv(socket, reinterpret_cast<char*>(data.data()), static_cast<int>(data.size()), MSG_WAITALL);
        #else
                recv(socket, data.data(), data.size(), MSG_WAITALL);
        #endif
            return;
        }
        uint32_t received = 0;

        while (received < data.size())
        {
#ifdef _WIN32
            int n = recv(socket, reinterpret_cast<char*>(data.data() + received), static_cast<int>(data.size() - received), 0);
#else
            ssize_t n = recv(socket, data.data() + received, data.size() - received, 0);
#endif

            if (n == 0)
                return;

            // if (n < 0)
            //     throw std::runtime_error("recv failed");

            received += static_cast<size_t>(n);
        }
    }

    void Send(Socket socket, std::span<const uint8_t> data)
    {
#ifdef _WIN32
        send(socket, reinterpret_cast<const char*>(data.data()), static_cast<int>(data.size()), 0);
#else
        send(socket, data.data(), data.size(), 0);
#endif
    }

    auto BuildSocketPath(const std::string& path) -> std::string
    {
#ifdef _WIN32
        return (std::filesystem::temp_directory_path() / "tilapia_daemon.sock").string();
#else
        return "/tmp/" + path;
#endif
    }

    void PollIn(std::span<const Socket> sockets, std::chrono::milliseconds timeout, std::move_only_function<void(Socket)> callback) {
        if(sockets.size() == 0)
            return;
#ifdef _WIN32
        auto* fds = (WSAPOLLFD*)alloca(sockets.size() * sizeof(WSAPOLLFD));

        for (size_t i = 0; i < sockets.size(); ++i)
            fds[i] = { (SOCKET)sockets[i], POLLIN, 0 };

        if (WSAPoll(fds, (ULONG)sockets.size(), (INT)timeout.count()) > 0)
            for (size_t i = 0; i < sockets.size(); ++i)
                if (fds[i].revents & POLLIN) callback(sockets[i]);
#else
        auto* fds = (pollfd*)alloca(sockets.size() * sizeof(pollfd));

        for (size_t i = 0; i < sockets.size(); ++i)
            fds[i] = { (int)sockets[i], POLLIN, 0 };

        if (poll(fds, sockets.size(), (int)timeout.count()) > 0)
            for (size_t i = 0; i < sockets.size(); ++i)
                if (fds[i].revents & POLLIN) callback(sockets[i]);
#endif
    }
}