module;

#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <format>
#include <print>
#include <vector>

export module tilapia.irlib:stringify;
import :ir;

export namespace Tilapia::IRLib
{
    constexpr std::string_view to_string(coreCaps v)
    {
        switch (v)
        {
        case coreCaps::time: return "time";
        case coreCaps::simd: return "simd";
        case coreCaps::random: return "random";
        case coreCaps::print: return "print";
        case coreCaps::tls: return "tls";
        case coreCaps::quic: return "quic";
        case coreCaps::http3: return "http3";
        case coreCaps::webtransport: return "webtransport";
        }

        return "unknown";
    }

    constexpr std::string_view to_string(symbolType v)
    {
        switch (v)
        {
        case symbolType::function: return "function";
        case symbolType::global: return "global";
        case symbolType::external: return "external";
        case symbolType::capability: return "capability";
        case symbolType::data: return "data";
        }

        return "unknown";
    }

    constexpr std::string_view to_string(entrypointType v)
    {
        switch (v)
        {
        case entrypointType::executable: return "executable";
        case entrypointType::library: return "library";
        case entrypointType::plugin: return "plugin";
        }

        return "unknown";
    }

    constexpr std::string_view to_string(coreCalls v)
    {
        switch (v)
        {
        case coreCalls::seed: return "seed";
        case coreCalls::next_u32: return "next_u32";
        case coreCalls::next_u64: return "next_u64";
        case coreCalls::next_f32: return "next_f32";
        case coreCalls::next_f64: return "next_f64";
        case coreCalls::fill_bytes: return "fill_bytes";
        case coreCalls::secure_fill_bytes: return "secure_fill_bytes";

        case coreCalls::print_str: return "print_str";
        case coreCalls::print_i32: return "print_i32";
        case coreCalls::print_i64: return "print_i64";
        case coreCalls::print_f32: return "print_f32";
        case coreCalls::print_f64: return "print_f64";
        case coreCalls::flush: return "flush";

        case coreCalls::tls_context_create: return "tls_context_create";
        case coreCalls::tls_handshake_start: return "tls_handshake_start";
        case coreCalls::tls_encrypt: return "tls_encrypt";
        case coreCalls::tls_decrypt: return "tls_decrypt";
        case coreCalls::tls_export_key_material: return "tls_export_key_material";
        case coreCalls::tls_close: return "tls_close";

        case coreCalls::quic_endpoint_create: return "quic_endpoint_create";
        case coreCalls::quic_connect: return "quic_connect";
        case coreCalls::quic_accept: return "quic_accept";
        case coreCalls::quic_stream_open: return "quic_stream_open";
        case coreCalls::quic_stream_accept: return "quic_stream_accept";
        case coreCalls::quic_stream_send: return "quic_stream_send";
        case coreCalls::quic_stream_recv: return "quic_stream_recv";
        case coreCalls::quic_datagram_send: return "quic_datagram_send";
        case coreCalls::quic_datagram_recv: return "quic_datagram_recv";
        case coreCalls::quic_close_stream: return "quic_close_stream";
        case coreCalls::quic_close_connection: return "quic_close_connection";

        case coreCalls::http3_session_create: return "http3_session_create";
        case coreCalls::http3_request_send: return "http3_request_send";
        case coreCalls::http3_response_recv: return "http3_response_recv";
        case coreCalls::http3_headers_send: return "http3_headers_send";
        case coreCalls::http3_headers_recv: return "http3_headers_recv";
        case coreCalls::http3_body_send: return "http3_body_send";
        case coreCalls::http3_body_recv: return "http3_body_recv";
        case coreCalls::http3_session_close: return "http3_session_close";

        case coreCalls::wt_session_create: return "wt_session_create";
        case coreCalls::wt_connect: return "wt_connect";
        case coreCalls::wt_accept: return "wt_accept";
        case coreCalls::wt_stream_open: return "wt_stream_open";
        case coreCalls::wt_stream_accept: return "wt_stream_accept";
        case coreCalls::wt_datagram_send: return "wt_datagram_send";
        case coreCalls::wt_datagram_recv: return "wt_datagram_recv";
        case coreCalls::wt_close: return "wt_close";
        }

        return "unknown_call";
    }

    constexpr std::string_view to_string(coreOpcodes op)
    {
        switch (op)
        {
        case coreOpcodes::nop: return "nop";
        case coreOpcodes::mov: return "mov";
        case coreOpcodes::li_i32: return "li_i32";
        case coreOpcodes::li_u32: return "li_u32";
        case coreOpcodes::li_f32: return "li_f32";
        case coreOpcodes::li64: return "li64";

        case coreOpcodes::load_u8: return "load_u8";
        case coreOpcodes::load_i16: return "load_i16";
        case coreOpcodes::load_i32: return "load_i32";
        case coreOpcodes::load_i64: return "load_i64";

        case coreOpcodes::store_u8: return "store_u8";
        case coreOpcodes::store_i16: return "store_i16";
        case coreOpcodes::store_i32: return "store_i32";
        case coreOpcodes::store_i64: return "store_i64";

        case coreOpcodes::alloc: return "alloc";
        case coreOpcodes::free: return "free";
        case coreOpcodes::memcpy: return "memcpy";
        case coreOpcodes::submem: return "submem";

        case coreOpcodes::call: return "call";
        case coreOpcodes::call_cap: return "call_cap";
        case coreOpcodes::call_lib: return "call_lib";
        case coreOpcodes::ret: return "ret";

        case coreOpcodes::jmp: return "jmp";
        case coreOpcodes::br_true: return "br_true";
        case coreOpcodes::br_false: return "br_false";
        case coreOpcodes::br_table: return "br_table";

        case coreOpcodes::add_i: return "add_i";
        case coreOpcodes::sub_i: return "sub_i";
        case coreOpcodes::mul_i: return "mul_i";
        case coreOpcodes::div_i: return "div_i";
        case coreOpcodes::mod_i: return "mod_i";

        case coreOpcodes::add_f: return "add_f";
        case coreOpcodes::sub_f: return "sub_f";
        case coreOpcodes::mul_f: return "mul_f";
        case coreOpcodes::div_f: return "div_f";

        case coreOpcodes::cmp_eq_i: return "cmp_eq_i";
        case coreOpcodes::cmp_lt_i: return "cmp_lt_i";
        case coreOpcodes::cmp_gt_i: return "cmp_gt_i";

        default:
            return "unknown_opcode";
        }
    }

    std::string reg(uint32_t v)
    {
        return std::format("RG {}", v);
    }

    std::string imm(uint32_t v)
    {
        return std::format("0x{:08X} | {}", v, v);
    }

    std::string imm_u8(uint32_t v)
    {
        uint8_t x = static_cast<uint8_t>(v);
        return std::format("0x{:02X} | {}", x, x);
    }

    std::string imm_u16(uint32_t v)
    {
        uint16_t x = static_cast<uint16_t>(v);
        return std::format("0x{:04X} | {}", x, x);
    }

    std::string imm_u32(uint32_t v)
    {
        return std::format("0x{:08X} | {}", v, v);
    }

    std::string imm_i8(uint32_t v)
    {
        int8_t x = static_cast<int8_t>(v);
        return std::format("0x{:02X} | {}", static_cast<uint8_t>(x), static_cast<int>(x));
    }

    std::string imm_i16(uint32_t v)
    {
        int16_t x = static_cast<int16_t>(v);
        return std::format("0x{:04X} | {}", static_cast<uint16_t>(x), x);
    }

    std::string imm_i32(uint32_t v)
    {
        int32_t x = static_cast<int32_t>(v);
        return std::format("0x{:08X} | {}", static_cast<uint32_t>(x), x);
    }

    std::string imm_f32(uint32_t bits)
    {
        float f = std::bit_cast<float>(bits);
        return std::format("0x{:08X} | {}", bits, f);
    }

    std::string imm_u64(uint32_t lo, uint32_t hi)
    {
        uint64_t v = uint64_t(lo) | (uint64_t(hi) << 32);
        return std::format("0x{:016X} | {}", v, v);
    }
}