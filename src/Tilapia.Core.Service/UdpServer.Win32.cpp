#include <cstdint>

#include "common.hpp"
#include "UdpServer.hpp"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

using namespace Tilapia::Service;

struct Tilapia::Service::NetContext
{
    RIO_BUF rioBuf;
    int connectionId;
};

struct Tilapia::Service::UdpServerContext
{
    RIO_EXTENSION_FUNCTION_TABLE rio;
    std::vector<RIORESULT> results;
    std::vector<NetContext> contextPool;
    RIO_CQ cq;
    RIO_RQ rq;
    WSAEVENT cqEvent;
    char* rawBuffer;
    SOCKET s;
    RIO_BUFFERID bufferId;
};

UdpServer::UdpServer(const UdpServerDesc& desc) :
    port(desc.port),
    packetSize(desc.packetSize),
    packetCount(desc.packetCount),
    bufferSize(desc.packetSize* desc.packetCount)
{
    serverContext = new UdpServerContext;

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    serverContext->s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    GUID functionTableId = WSAID_MULTIPLE_RIO;
    DWORD dwBytes = 0;
    if (WSAIoctl(serverContext->s, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER,
        &functionTableId, sizeof(GUID),
        (void**)&serverContext->rio, sizeof(serverContext->rio), &dwBytes, 0, 0) != 0)
    {
        std::println("RIO loading fail"); return;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(desc.port);
    bind(serverContext->s, (struct sockaddr*)&server, sizeof(server));

    serverContext->rawBuffer = (char*)VirtualAlloc(NULL, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    serverContext->bufferId = serverContext->rio.RIORegisterBuffer(serverContext->rawBuffer, bufferSize);

    serverContext->cqEvent = WSACreateEvent();
    RIO_NOTIFICATION_COMPLETION notify = { RIO_EVENT_COMPLETION, {serverContext->cqEvent, FALSE} };

    serverContext->cq = serverContext->rio.RIOCreateCompletionQueue(desc.packetCount * 2, &notify);
    serverContext->rq = serverContext->rio.RIOCreateRequestQueue(serverContext->s,
        desc.packetCount, 1,
        desc.packetCount, 1,
        serverContext->cq, serverContext->cq, NULL);

    serverContext->contextPool.resize(desc.packetCount);

    for (int i = 0; i < desc.packetCount; ++i) {
        serverContext->contextPool[i].rioBuf.BufferId = serverContext->bufferId;
        serverContext->contextPool[i].rioBuf.Offset = i * desc.packetSize;
        serverContext->contextPool[i].rioBuf.Length = desc.packetSize;
        serverContext->contextPool[i].connectionId = 0;

        serverContext->rio.RIOReceive(serverContext->rq,
            &(serverContext->contextPool[i].rioBuf),
            1, 0, &serverContext->contextPool[i]);
    }
    serverContext->results.resize(desc.packetCount);

    std::println("RIO: Server listening to port {}", desc.port);
}

UdpServer::~UdpServer()
{
    std::println("Closing UDP Server...");

    if (serverContext->s != INVALID_SOCKET) {
        closesocket(serverContext->s);
    }
    if (serverContext->rq != RIO_INVALID_RQ) {

    }
    if (serverContext->cq != RIO_INVALID_CQ) {
        serverContext->rio.RIOCloseCompletionQueue(serverContext->cq);
    }

    if (serverContext->bufferId != RIO_INVALID_BUFFERID) {
        serverContext->rio.RIODeregisterBuffer(serverContext->bufferId);
    }

    if (serverContext->rawBuffer != nullptr) {
        VirtualFree(serverContext->rawBuffer, 0, MEM_RELEASE);
    }

    if (serverContext->cqEvent != WSA_INVALID_EVENT) {
        WSACloseEvent(serverContext->cqEvent);
    }
    WSACleanup();
    delete serverContext;
}

auto UdpServer::MainLoop()
{
    while (true) {
        ULONG numResults = serverContext->rio.RIODequeueCompletion(serverContext->cq, serverContext->results.data(), packetCount);

        if (numResults == 0) {
            serverContext->rio.RIONotify(serverContext->cq);
            WSAWaitForMultipleEvents(1, &serverContext->cqEvent, TRUE, WSA_INFINITE, FALSE);
            WSAResetEvent(serverContext->cqEvent);
            continue;
        }

        for (ULONG i = 0; i < numResults; ++i) {
            auto* compCtx = reinterpret_cast<NetContext*>(serverContext->results[i].RequestContext);

            std::string_view payload(
                serverContext->rawBuffer + compCtx->rioBuf.Offset,
                serverContext->results[i].BytesTransferred
            );

            std::println("[Procesing] Context ID: {} | Bytes: {} | Data: {}",
                compCtx->connectionId,
                serverContext->results[i].BytesTransferred,
                payload);

            serverContext->rio.RIOReceive(serverContext->rq, &(compCtx->rioBuf), 1, 0, reinterpret_cast<PVOID>(compCtx));
        }
    }
}
#endif