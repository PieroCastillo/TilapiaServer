#include <cstdint>
#include <filesystem>
#include <span>
#include <string>
#include <string_view>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <tchar.h>
#include <tlhelp32.h>
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

    bool EnsureSingle()
    {
        HANDLE hMutex = nullptr;
        constexpr wchar_t kMutexName[] = L"Global\\Tilapia_Daemon_UniqueMutex";
        hMutex = CreateMutexW(nullptr, TRUE, kMutexName);
        if (!hMutex)
            return false;

        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            CloseHandle(hMutex);
            hMutex = nullptr;
            return false;
        }
        return true;
    }

    auto RunProcess(const std::filesystem::path& appPath, std::span<const std::string> args, bool detached) -> Process
    {
        auto cmd = makeCmd(args);

        STARTUPINFOA si{};
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi{};

        /*
        if is detached, child process does not inherit handles
        */
        if (!CreateProcessA(appPath.string().c_str(), cmd.data(), 0, 0,
            !detached, detached ? (DETACHED_PROCESS | CREATE_BREAKAWAY_FROM_JOB) : 0,
            0, 0, &si, &pi))
        {

        }
        CloseHandle(pi.hThread);
        if (detached)
            CloseHandle(pi.hProcess);
        Process p = { (uint32_t)pi.dwProcessId, detached ? 0 : (uint64_t)pi.hProcess };
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

    void KillProcessByName(const std::string& appname)
    {
        auto exeName = appname + ".exe";

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE)
            return;

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(pe);

        if (Process32First(snapshot, &pe))
        {
            do
            {
                if (_stricmp(pe.szExeFile, exeName.c_str()) == 0)
                {
                    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);

                    if (hProcess)
                    {
                        TerminateProcess(hProcess, 0);
                        CloseHandle(hProcess);
                    }
                }
            } while (Process32Next(snapshot, &pe));
        }

        CloseHandle(snapshot);
    }
}
#endif