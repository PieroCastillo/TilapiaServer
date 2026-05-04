module;

#include <tuple>
#include <vector>
#include "common.hpp"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <windows.h>
#include <tchar.h>
#endif

module tilapia.platform;

import std;

#ifdef _WIN32

namespace Tilapia::Daemon
{
    void ensureSingle()
    {

    }

    SharedMemory::~SharedMemory()
    {
        if (data)
            UnmapViewOfFile(data);

        if (handle)
            CloseHandle((HANDLE)handle);

        data = nullptr;
        handle = 0;
        size = 0;
    }

    auto sharedAlloc(uint32_t size) -> SharedMemory
    {
        HANDLE h = CreateFileMappingA(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, size, nullptr);

        if (!h)
            return {};

        auto p = (uint8_t*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, size);

        if (!p)
        {
            CloseHandle(h);
            return {};
        }

        return { p, size, (uint64_t)h };
    }

    auto sharedOpen(uint64_t inherited) -> SharedMemory
    {
        auto p = (uint8_t*)MapViewOfFile((HANDLE)inherited, FILE_MAP_ALL_ACCESS, 0, 0, 0);

        if (!p)
            return {};

        return { p, 0, inherited };
    }
}
#endif