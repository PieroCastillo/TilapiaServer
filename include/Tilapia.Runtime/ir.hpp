/*
Created by @PieroCastillo on 2026-04-16
*/
#ifndef TILAPIA_RUNTIME_IR_HPP
#define TILAPIA_RUNTIME_IR_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace TilapiaServer::Runtime::IR
{
    /*
    FORMAT : 0xDDSSOOOO
    DD = domain
    SS = subdomain
    OOOO = opcode index
    */
    enum class coreCaps : uint16_t
    {
        control = 0x0000,
        alu = 0x0001,
        memory = 0x0002,
        time = 0x0003,
        simd = 0x0004,
        random = 0x0005,
        print = 0x0006,
        tls13 = 0x0010,
        quic = 0x0011,
        http3 = 0x0012,
        webtransport = 0x0013,
    };

    enum class coreDatatype : uint16_t
    {
        u8 = 0x0001,
        u16 = 0x0002,
        u32 = 0x0004,
        u64 = 0x0008,
        u128 = 0x0010,
        i8 = 0x0011,
        i16 = 0x0012,
        i32 = 0x0014,
        i64 = 0x0018,
        f32 = 0x0024,
        f64 = 0x0028,
        boolean = 0x0031,

        memhandle = 0x0100,
        reshandle = 0x0200,
        string = 0x0300,
        span = 0x0400,
    };

    enum class coreOpcodes : uint32_t
    {
        // CONTROL : 0x0000
        nop = 0x00000000,
        push_var = 0x00000001,
        push_imm_i32 = 0x00000002,
        push_const = 0x00000003,
        pop_var = 0x00000004,
        call_local = 0x00000005,
        call_cap = 0x00000006,
        call_ext = 0x00000007,

        // ALU INT : 0x0001
        add_i = 0x00010001,
        sub_i = 0x00010002,
        mul_i = 0x00010003,
        div_i = 0x00010004,
        mod_i = 0x00010005,

        // ALU FLOAT : 0x0001
        add_f = 0x00010006,
        sub_f = 0x00010007,
        mul_f = 0x00010008,
        div_f = 0x00010009,

        // ALU BITWISE/LOGIC : 0x0001
        and_b = 0x0001000A,
        or_b = 0x0001000B,
        xor_b = 0x0001000C,
        not_b = 0x0001000D,
        shl_b = 0x0001000E,
        shr_b = 0x0001000F,

        // ALU COMP INT : 0x0001
        cmp_eq_i = 0x00010010,
        cmp_ne_i = 0x00010011,
        cmp_lt_i = 0x00010012,
        cmp_gt_i = 0x00010013,

        // ALU COMP FLOAT : 0x0001
        cmp_eq_f = 0x00010014,
        cmp_lt_f = 0x00010015,
        cmp_gt_f = 0x00010016,

        // MEMORY : 0x0002
        load_u8 = 0x00020001,
        load_i32 = 0x00020002,
        load_i64 = 0x00020003,
        load_f64 = 0x00020004,

        store_u8 = 0x00020005,
        store_i32 = 0x00020006,
        store_i64 = 0x00020007,
        store_f64 = 0x00020008,

        memcpy = 0x00020009,
        memmove = 0x0002000A,
        memset = 0x0002000B,

        alloc = 0x0002000C,
        free = 0x0002000D,
        protect = 0x0002000E,

        // EXTENSION OPERATIONS

        // TIME : 0x0003
        now_monotonic = 0x00030001,
        now_wallclock = 0x00030002,

        // SIMD INT : 0x0004
        vadd_i = 0x00040001,
        vsub_i = 0x00040002,
        vmul_i = 0x00040003,
        vdiv_i = 0x00040004,

        // SIMD FLOAT : 0x0004
        vadd_f = 0x00040005,
        vsub_f = 0x00040006,
        vmul_f = 0x00040007,
        vdiv_f = 0x00040008,

        // SIMD BITWISE : 0x0004
        vand_b = 0x00040009,
        vor_b = 0x0004000A,
        vxor_b = 0x0004000B,

        // SIMD MEMORY/UTILS : 0x0004
        vload = 0x0004000C,
        vstore = 0x0004000D,
        vshuffle = 0x0004000E,
        vreduce_add_i = 0x0004000F,
        vreduce_add_f = 0x00040010,
    };

    enum class coreCalls : uint32_t
    {
        // RANDOM : 0x0005
        seed = 0x00050001,
        next_u32 = 0x00050002,
        next_u64 = 0x00050003,
        next_f32 = 0x00050004,
        next_f64 = 0x00050005,
        fill_bytes = 0x00050006,
        secure_fill_bytes = 0x00050007,

        // PRINT / DEBUG : 0x0006
        print_str = 0x00060001,
        print_i32 = 0x00060002,
        print_i64 = 0x00060003,
        print_f32 = 0x00060004,
        print_f64 = 0x00060005,
        flush = 0x00060006,

        // TLS 1.3 : 0x1000
        tls_context_create = 0x10000001,
        tls_handshake_start = 0x10000002,
        tls_encrypt = 0x10000003,
        tls_decrypt = 0x10000004,
        tls_export_key_material = 0x10000005,
        tls_close = 0x10000006,

        // QUIC : 0x1100
        quic_endpoint_create = 0x11000001,
        quic_connect = 0x11000002,
        quic_accept = 0x11000003,
        quic_stream_open = 0x11000004,
        quic_stream_accept = 0x11000005,
        quic_stream_send = 0x11000006,
        quic_stream_recv = 0x11000007,
        quic_datagram_send = 0x11000008,
        quic_datagram_recv = 0x11000009,
        quic_close_stream = 0x1100000A,
        quic_close_connection = 0x1100000B,

        // HTTP/3 : 0x1200
        http3_session_create = 0x12000001,
        http3_request_send = 0x12000002,
        http3_response_recv = 0x12000003,
        http3_headers_send = 0x12000004,
        http3_headers_recv = 0x12000005,
        http3_body_send = 0x12000006,
        http3_body_recv = 0x12000007,
        http3_session_close = 0x12000008,

        // WEBTRANSPORT : 0x1300
        wt_session_create = 0x13000001,
        wt_connect = 0x13000002,
        wt_accept = 0x13000003,
        wt_stream_open = 0x13000004,
        wt_stream_accept = 0x13000005,
        wt_datagram_send = 0x13000006,
        wt_datagram_recv = 0x13000007,
        wt_close = 0x13000008,
    };

    enum class symbolType : uint16_t
    {
        function,
        global,
        external,
        capability,
        data,
    };

    enum class entrypointType : uint16_t
    {
        executable,
        library,
        plugin,
    };

    enum class resourceFlags : uint32_t
    {
        none = 0,
        readable = 1 << 0,
        writable = 1 << 1,
        executable = 1 << 2,
        network = 1 << 3,
        filesystem = 1 << 4,
        gpu = 1 << 5,
    };

    struct header
    {
        uint32_t magic = 0x74694952; // "tiIR"
        uint16_t versionMajor = 1;
        uint16_t versionMinor = 0;
        uint32_t flags;
        uint32_t entrypointOffset;
        std::string executableName;
    };

    struct capabilityEntry
    {
        uint16_t capId;
        uint16_t versionMajor;
        uint16_t versionMinor;
        uint32_t flags;
    };

    struct type
    {
        uint32_t offset;
        uint32_t subtypeCount;
    };

    struct dynamicLibRef
    {
        uint64_t version;
        uint32_t symbolOffset;
        uint32_t flags;
    };

    struct dataEntry
    {
        uint32_t size;
        uint8_t dataOffset;
        uint32_t alignment;
    };

    struct symbolEntry
    {
        symbolType type;
        uint32_t offset;
        uint32_t size;
        uint32_t flags;
    };

    struct entrypoint
    {
        entrypointType type;
        uint32_t instructionOffset;
        uint32_t flags;
    };

    struct functionEntry
    {
        uint32_t startInstructionOffset;
        uint32_t instructionCount;
        uint16_t paramCount;
        uint16_t flags;
    };


    struct alignas(16) instruction
    {
        uint16_t capId;
        uint16_t opCode;
        uint32_t op1, op2, op3;
    };

    struct binary
    {
        header header;
        std::vector<capabilityEntry> capabilities;
        std::vector<type> types;
        std::vector<uint8_t> typesPool;
        std::vector<symbolEntry> symbols;
        // std::vector<dynamicLibRef> dynamicLibs;
        std::vector<entrypoint> entrypoints;
        std::vector<functionEntry> functions;
        std::vector<dataEntry> readOnlyData;
        std::vector<uint8_t> readOnlyDataPool;
        std::vector<dataEntry> readWriteData;
        std::vector<uint8_t> readWriteDataPool;
        std::vector<instruction> instructions;
    };
};
#endif // TILAPIA_RUNTIME_IR_HPP