/*
Created by @PieroCastillo on 2026-04-16
*/
#ifndef TILAPIA_CORE_SERVICE_API_HPP
#define TILAPIA_CORE_SERVICE_API_HPP

#ifdef _INTELLISENSE
    #include <array>
    #include <algorithm>
    #include <atomic>
    #include <concepts>
    #include <condition_variable>
    #include <expected>
    #include <filesystem>
    #include <map>
    #include <memory>
    #include <mutex>
    #include <optional>
    #include <print>
    #include <span>
    #include <stdexcept>
    #include <string>
    #include <string_view>
    #include <tuple>
    #include <thread>
    #include <type_traits>
    #include <unordered_map>
    #include <utility>
    #include <variant>
    #include <vector>
#else 
    import std;
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

bool net_init() { 
    WSADATA wsa; return WSAStartup(MAKEWORD(2, 2), &wsa) == 0;
}
void net_cleanup() {
    WSACleanup();
}
void net_close_socket(SOCKET s) {
    closesocket(s);
}
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

bool net_init() {
    return true;
}
void net_cleanup() {
    // no requiere cleanup
}
void net_close_socket(int s) {
    close(s);
}
#endif

#endif // TILAPIA_CORE_SERVICE_API_HPP

// copy & paste this code every file that includes this header
#ifndef _INTELLISENSE
    import std;
#endif