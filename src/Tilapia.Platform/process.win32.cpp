#include <cstdint>
#include <filesystem>
#include <span>
#include <string>
#include <string_view>

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
    auto makeCmd(std::span<const std::string> args) -> std::string
    {
        std::string cmd;
        bool first = true;

        for (std::string_view arg : args)
        {
            if (!first)
                cmd += ' ';
            first = false;

            bool needs_quotes =
                arg.empty() ||
                arg.find_first_of(" \t\"") != std::string_view::npos;

            if (!needs_quotes)
            {
                cmd += arg;
                continue;
            }

            cmd += '"';

            size_t backslashes = 0;
            for (char c : arg)
            {
                if (c == '\\')
                {
                    ++backslashes;
                }
                else if (c == '"')
                {
                    cmd.append(backslashes * 2 + 1, '\\');
                    cmd += '"';
                    backslashes = 0;
                }
                else
                {
                    cmd.append(backslashes, '\\');
                    backslashes = 0;
                    cmd += c;
                }
            }

            cmd.append(backslashes * 2, '\\');
            cmd += '"';
        }

        return cmd;
    }

    void EnsureSingle()
    {

    }

    auto RunProcess(const std::filesystem::path& appPath, std::span<const std::string> args) -> Process
    {
        auto cmd = makeCmd(args);

        STARTUPINFOA si{};
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi{};

        if (!CreateProcessA(appPath.string().c_str(), cmd.data(), 0, 0, true, 0, 0, 0, &si, &pi))
        {

        }
        CloseHandle(pi.hThread);
        Process p = { (uint32_t)pi.dwProcessId, (uint64_t)pi.hProcess };
        return p;
    }

    void DetachProcess(const Process& process)
    {
        CloseHandle((HANDLE)process.handle);
    }

    void KillProcess(const Process& process)
    {
        TerminateProcess((HANDLE)process.handle, 0);
        CloseHandle((HANDLE)process.handle);
    }
}
#endif