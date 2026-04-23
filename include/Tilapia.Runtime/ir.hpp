/*
Created by @PieroCastillo on 2026-04-16
*/
#ifndef TILAPIA_RUNTIME_IR_HPP
#define TILAPIA_RUNTIME_IR_HPP

#include <cstdint>

namespace TilapiaServer::Runtime::IR
{
    using opcode_t = uint32_t;
    /*
    FORMAT : 0xDDSSOOOO
    DD = domain
    SS = subdomain
    OOOO = opcode index
    */
    enum class coreOpcodes : opcode_t
    {
        // ALU : 01
        add = 0x00010001,
        sub = 0x00010002,
        mul = 0x00010003,
        div = 0x00010004,
        mod = 0x00010005,
        neg = 0x00010006,

        and_ = 0x00010007,
        or_ = 0x00010008,
        xor_ = 0x00010009,
        not_ = 0x0001000A,

        shl = 0x0001000B,
        shr = 0x0001000C,

        cmp_eq = 0x0001000D,
        cmp_ne = 0x0001000E,
        cmp_lt = 0x0001000F,
        cmp_le = 0x00010010,
        cmp_gt = 0x00010011,
        cmp_ge = 0x00010012,

        // TIME: 02
        now_monotonic = 0x00020001,
        now_wallclock = 0x00020002,

        sleep_ns = 0x00020003,
        sleep_until = 0x00020004,

        timer_create = 0x00020005,
        timer_cancel = 0x00020006,

        // RANDOM : 03
        seed = 0x00030001,
        next_u32 = 0x00030002,
        next_u64 = 0x00030003,
        next_f32 = 0x00030004,
        next_f64 = 0x00030005,
        fill_bytes = 0x00030006,
        secure_fill_bytes = 0x00030007,

        // PRINT / DEBUG : 04
        print = 0x00040001,
        print_i32 = 0x00040002,
        print_i64 = 0x00040003,
        print_f32 = 0x00040004,
        print_f64 = 0x00040005,
        print_str = 0x00040006,
        flush = 0x00040007,

        // MEMORY : 05
        load = 0x00050001,
        store = 0x00050002,

        load8 = 0x00050003,
        load16 = 0x00050004,
        load32 = 0x00050005,
        load64 = 0x00050006,

        store8 = 0x00050007,
        store16 = 0x00050008,
        store32 = 0x00050009,
        store64 = 0x0005000A,

        memcpy = 0x0005000B,
        memmove = 0x0005000C,
        memset = 0x0005000D,

        alloc = 0x0005000E,
        free = 0x0005000F,

        protect = 0x00050010,

        // ATOMIC : 06
        atomic_load = 0x00060001,
        atomic_store = 0x00060002,

        exchange = 0x00060003,
        compare_exchange = 0x00060004,

        fetch_add = 0x00060005,
        fetch_sub = 0x00060006,

        fetch_and = 0x00060007,
        fetch_or = 0x00060008,
        fetch_xor = 0x00060009,

        fence = 0x0006000A,

        // SYNC : 07
        spawn = 0x00070001,
        join = 0x00070002,
        yield = 0x00070003,

        park = 0x00070004,
        unpark = 0x00070005,

        mutex_lock = 0x00070006,
        mutex_unlock = 0x00070007,

        semaphore_wait = 0x00070008,
        semaphore_post = 0x00070009,

        event_wait = 0x0007000A,
        event_signal = 0x0007000B,

        // SIMD : 08
        vadd = 0x00080001,
        vsub = 0x00080002,
        vmul = 0x00080003,
        vdiv = 0x00080004,

        vand = 0x00080005,
        vor = 0x00080006,
        vxor = 0x00080007,

        vload = 0x00080008,
        vstore = 0x00080009,

        vshuffle = 0x0008000A,
        vreduce_add = 0x0008000B,

        // TLS 1.3 :  10
        tls_context_create = 0x00100001,
        tls_handshake_start = 0x00100002,
        tls_encrypt = 0x00100003,
        tls_decrypt = 0x00100004,
        tls_export_key_material = 0x00100005,
        tls_close = 0x00100006,

        // QUIC : 11
        quic_endpoint_create = 0x00110001,
        quic_connect = 0x00110002,
        quic_accept = 0x00110003,

        quic_stream_open = 0x00110004,
        quic_stream_accept = 0x00110005,

        quic_stream_send = 0x00110006,
        quic_stream_recv = 0x00110007,

        quic_datagram_send = 0x00110008,
        quic_datagram_recv = 0x00110009,

        quic_close_stream = 0x0011000A,
        quic_close_connection = 0x0011000B,

        // HTTP/3 : 12
        http3_session_create = 0x00120001,
        http3_request_send = 0x00120002,
        http3_response_recv = 0x00120003,

        http3_headers_send = 0x00120004,
        http3_headers_recv = 0x00120005,

        http3_body_send = 0x00120006,
        http3_body_recv = 0x00120007,

        http3_session_close = 0x00120008,

        // WEBTRANSPORT : 13
        wt_session_create = 0x00130001,

        wt_connect = 0x00130002,
        wt_accept = 0x00130003,

        wt_stream_open = 0x00130004,
        wt_stream_accept = 0x00130005,

        wt_datagram_send = 0x00130006,
        wt_datagram_recv = 0x00130007,

        wt_close = 0x00130008,
    };

    struct instruction
    {
        uint16_t capId;
        uint16_t opCode;
        uint32_t op1, op2, op3;
    };

    struct instructionExt
    {
        uint16_t capId;
        uint16_t opCode;
        uint32_t op1, op2, op3;
        uint32_t ext1, ext2, ext3, ext4;
    };
};

#endif // TILAPIA_RUNTIME_IR_HPP