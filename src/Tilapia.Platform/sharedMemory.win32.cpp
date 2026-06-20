#include <tuple>
#include <vector>

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

import std;
import tilapia.platform;

#ifdef _WIN32

namespace Tilapia::Platform
{
    SharedMemory::~SharedMemory()
    {
        if (data)
            UnmapViewOfFile(data);
        
            data = nullptr;
        handle = 0;
        size = 0;

        if (handle && !isOwner)
            CloseHandle((HANDLE)handle);
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

        return SharedMemory(p, size, (uint64_t)h, true);
    }

    auto sharedOpen(uint64_t inherited, uint32_t size) -> SharedMemory
    {
        auto p = (uint8_t*)MapViewOfFile((HANDLE)inherited, FILE_MAP_ALL_ACCESS, 0, 0, 0);

        if (!p)
            return {};

        return SharedMemory(p, size, inherited, false);
    }
}
#endif