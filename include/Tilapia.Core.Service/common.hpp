/*
Created by @PieroCastillo on 2026-04-16
*/
#ifndef TILAPIA_CORE_SERVICE_API_HPP
#define TILAPIA_CORE_SERVICE_API_HPP

#ifdef _INTELLISENSE
#include <any>
#include <array>
#include <algorithm>
#include <atomic>
#include <concepts>
#include <cstdint>
#include <condition_variable>
#include <expected>
#include <filesystem>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <optional>
#include <print>
#include <queue>
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
#endif

// #ifdef _WIN32
// #include <winsock2.h>
// #include <ws2tcpip.h>
// #include <mswsock.h>
// #pragma comment(lib, "ws2_32.lib")

// SOCKET s;
// RIO_EXTENSION_FUNCTION_TABLE rioFunctions;

// bool netInit() {
//     s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//     WSADATA wsa;
//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//         return false;
//     }
//     GUID functionTableId = WSAID_MULTIPLE_RIO;
//     DWORD dwBytes = 0;

//     return !(WSAIoctl(s, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER,
//         &functionTableId, sizeof(GUID),
//         (void**)&rioFunctions, sizeof(rioFunctions),
//         &dwBytes, 0, 0) != 0);
// }
// void netCleanup() {
//     closesocket(s);
//     WSACleanup();
// }
// void netCloseSocket(SOCKET socket) {
//     closesocket(socket);
// }
// #else
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netdb.h>
// #include <unistd.h>
// #include <liburing.h>
// io_uring ring;

// bool netInit() {
//     return !(io_uring_queue_init(4096, &ring, 0) < 0);
// }
// void netCleanup() {
//     io_uring_queue_exit(&ring);
// }
// void netCloseSocket(int s) {
//     close(s);
// }
// #endif

#endif // TILAPIA_CORE_SERVICE_API_HPP

// copy & paste this code every file that includes this header
#ifndef _INTELLISENSE
import std;
#endif