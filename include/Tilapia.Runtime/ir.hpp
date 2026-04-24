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
        control      = 0x0000,
        alu          = 0x0001,
        time         = 0x0002,
        random       = 0x0003,
        print        = 0x0004,
        memory       = 0x0005,
        atomic       = 0x0006,
        sync         = 0x0007,
        simd         = 0x0008,
        tls13        = 0x0010,
        quic         = 0x0011,
        http3        = 0x0012,
        webtransport = 0x0013,
    };

    enum class coreDatatype : uint16_t
    {
        u8        = 0x0001,
        u16       = 0x0002,
        u32       = 0x0004,
        u64       = 0x0008,
        u128      = 0x0010,
        i8        = 0x0011,
        i16       = 0x0012,
        i32       = 0x0014,
        i64       = 0x0018,
        f32       = 0x0024,
        f64       = 0x0028,
        boolean   = 0x0031,

        memhandle = 0x0100,
        reshandle = 0x0200,
        string    = 0x0300,
        span      = 0x0400,
    };

    enum class coreBaseOpcodes : uint32_t
    {   
        // CONTROL : 0x00
        nop          = 0x00000000,
        push_var     = 0x00000010,
        push_imm_i32 = 0x00000011,
        push_const   = 0x00000012,
        pop_var      = 0x00000015,
        call_local   = 0x00000020,
        call_cap     = 0x00000021,
        call_ext     = 0x00000022,

        // ALU INT : 0x0100
        add_i        = 0x01000001,
        sub_i        = 0x01000002,
        mul_i        = 0x01000003,
        div_i        = 0x01000004,
        mod_i        = 0x01000005,

        // ALU FLOAT : 0x0101
        add_f        = 0x01010001,
        sub_f        = 0x01010002,
        mul_f        = 0x01010003,
        div_f        = 0x01010004,

        // ALU BITWISE/LOGIC : 0x0102
        and_b        = 0x01020001,
        or_b         = 0x01020002,
        xor_b        = 0x01020003,
        not_b        = 0x01020004,
        shl_b        = 0x01020005,
        shr_b        = 0x01020006,

        // ALU COMP INT : 0x0103
        cmp_eq_i     = 0x01030001,
        cmp_ne_i     = 0x01030002,
        cmp_lt_i     = 0x01030003,
        cmp_gt_i     = 0x01030004,

        // ALU COMP FLOAT : 0x0104
        cmp_eq_f     = 0x01040001,
        cmp_lt_f     = 0x01040002,
        cmp_gt_f     = 0x01040003,

        // MEMORY : 0x05
        load_u8      = 0x05000001,
        load_i32     = 0x05000002,
        load_i64     = 0x05000003,
        load_f64     = 0x05000004,

        store_u8     = 0x05010001,
        store_i32    = 0x05010002,
        store_i64    = 0x05010003,
        store_f64    = 0x05010004,

        memcpy       = 0x05020001,
        memmove      = 0x05020002,
        memset       = 0x05020003,

        alloc        = 0x05030001,
        free         = 0x05030002,
        protect      = 0x05030003,
    };

    enum class coreExtCalls : uint32_t
    {
        // TIME : 0x02
        now_monotonic = 0x02000001,
        now_wallclock = 0x02000002,    
        
        // SIMD INT : 0x0800
        vadd_i        = 0x08000001,
        vsub_i        = 0x08000002,
        vmul_i        = 0x08000003,
        vdiv_i        = 0x08000004,

        // SIMD FLOAT : 0x0801
        vadd_f        = 0x08010001,
        vsub_f        = 0x08010002,
        vmul_f        = 0x08010003,
        vdiv_f        = 0x08010004,

        // SIMD BITWISE : 0x0802
        vand_b        = 0x08020001,
        vor_b         = 0x08020002,
        vxor_b        = 0x08020003,

        // SIMD MEMORY/UTILS : 0x0803
        vload         = 0x08030001,
        vstore        = 0x08030002,
        vshuffle      = 0x08030003,
        vreduce_add_i = 0x08030004,
        vreduce_add_f = 0x08030005,
    };

    enum class coreCalls : uint32_t
    {
        // RANDOM : 0x03
        seed              = 0x03000001,
        next_u32          = 0x03000002,
        next_u64          = 0x03000003,
        next_f32          = 0x03000004,
        next_f64          = 0x03000005,
        fill_bytes        = 0x03000006,
        secure_fill_bytes = 0x03000007,

        // PRINT / DEBUG : 0x04
        print_str         = 0x04000001,
        print_i32         = 0x04000002,
        print_i64         = 0x04000003,
        print_f32         = 0x04000004,
        print_f64         = 0x04000005,
        flush             = 0x04000006,

        // TLS 1.3 : 0x10
        tls_context_create      = 0x10000001,
        tls_handshake_start     = 0x10000002,
        tls_encrypt             = 0x10000003,
        tls_decrypt             = 0x10000004,
        tls_export_key_material = 0x10000005,
        tls_close               = 0x10000006,

        // QUIC : 0x11
        quic_endpoint_create    = 0x11000001,
        quic_connect            = 0x11000002,
        quic_accept             = 0x11000003,
        quic_stream_open        = 0x11000004,
        quic_stream_accept      = 0x11000005,
        quic_stream_send        = 0x11000006,
        quic_stream_recv        = 0x11000007,
        quic_datagram_send      = 0x11000008,
        quic_datagram_recv      = 0x11000009,
        quic_close_stream       = 0x1100000A,
        quic_close_connection   = 0x1100000B,

        // HTTP/3 : 0x12
        http3_session_create    = 0x12000001,
        http3_request_send      = 0x12000002,
        http3_response_recv     = 0x12000003,
        http3_headers_send      = 0x12000004,
        http3_headers_recv      = 0x12000005,
        http3_body_send         = 0x12000006,
        http3_body_recv         = 0x12000007,
        http3_session_close     = 0x12000008,

        // WEBTRANSPORT : 0x13
        wt_session_create       = 0x13000001,
        wt_connect              = 0x13000002,
        wt_accept               = 0x13000003,
        wt_stream_open          = 0x13000004,
        wt_stream_accept        = 0x13000005,
        wt_datagram_send        = 0x13000006,
        wt_datagram_recv        = 0x13000007,
        wt_close                = 0x13000008,
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