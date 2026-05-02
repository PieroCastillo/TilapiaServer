module;

#include <cstdint>
#include <string>
#include <vector>

export module tilapia.irlib:ir;

export namespace Tilapia::IRLib
{
    /*
    00 caps are reserved for ext operations
    */
    enum class coreCaps : uint16_t
    {
        time = 0x0006,
        simd = 0x0007,
        random = 0x0008,
        print = 0x0009,
        tls = 0x1000,
        quic = 0x1100,
        http3 = 0x1200,
        webtransport = 0x1300,
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
        mov = 0x00000001,
        li_i32 = 0x00000002,
        li_u32 = 0x00000003,
        li_f32 = 0x00000004,
        li64 = 0x00000005,
        load_u8 = 0x00000006,
        load_i16 = 0x00000007,
        load_i32 = 0x00000008,
        load_i64 = 0x00000009,
        load_f32 = 0x0000000A,
        load_f64 = 0x0000000B,
        store_u8 = 0x0000000C,
        store_i16 = 0x0000000D,
        store_i32 = 0x0000000E,
        store_i64 = 0x0000000F,
        store_f32 = 0x00000010,
        store_f64 = 0x00000011,
        s_addr = 0x00000012,
        alloc = 0x00000013,
        free = 0x00000014,
        memcpy = 0x00000015,
        submem = 0x00000016,
        call = 0x00000017,
        call_cap = 0x00000018,
        call_lib = 0x00000019,
        ret = 0x0000001A,
        jmp = 0x0000001B,
        br_true = 0x0000001C,
        br_false = 0x0000001D,
        br_table = 0x0000001E,

        // ALU INT : 0x0001
        add_i = 0x00010001,
        sub_i = 0x00010002,
        mul_i = 0x00010003,
        div_i = 0x00010004,
        mod_i = 0x00010005,

        // ALU FLOAT : 0x0002
        add_f = 0x00020001,
        sub_f = 0x00020002,
        mul_f = 0x00020003,
        div_f = 0x00020004,

        // ALU BITWISE/LOGIC : 0x0003
        and_b = 0x00030001,
        or_b = 0x00030002,
        xor_b = 0x00030003,
        not_b = 0x00030004,
        shl_b = 0x00030005,
        shr_b = 0x00030006,

        // ALU COMP INT : 0x0004
        cmp_eq_i = 0x00040001,
        cmp_ne_i = 0x00040002,
        cmp_lt_i = 0x00040003,
        cmp_gt_i = 0x00040004,

        // ALU COMP FLOAT : 0x0005
        cmp_eq_f = 0x00050001,
        cmp_lt_f = 0x00050002,
        cmp_gt_f = 0x00050003,

        // TIME : 0x0006
        now_monotonic = 0x00060001,
        now_wallclock = 0x00060002,

        // SIMD : 0x0007
        vsetvl = 0x00070001,
        vload = 0x00070002,
        vstore = 0x00070003,
        vgather = 0x00070004,
        vscatter = 0x00070005,
        vbroadcast_s = 0x00070006,
        vadd_i = 0x00070007,
        vsub_i = 0x00070008,
        vmul_i = 0x00070009,
        vdiv_i = 0x0007000A,
        vmod_i = 0x0007000B,
        vmin_i = 0x0007000C,
        vmax_i = 0x0007000D,
        vabs_i = 0x0007000E,
        vadd_vs_i = 0x0007000F,
        vsub_vs_i = 0x00070010,
        vmul_vs_i = 0x00070011,
        vdiv_vs_i = 0x00070012,
        vadd_f = 0x00070013,
        vsub_f = 0x00070014,
        vmul_f = 0x00070015,
        vdiv_f = 0x00070016,
        vmin_f = 0x00070017,
        vmax_f = 0x00070018,
        vabs_f = 0x00070019,
        vsqrt_f = 0x0007001A,
        vfma_f = 0x0007001B,
        vfms_f = 0x0007001C,
        vadd_vs_f = 0x0007001D,
        vmul_vs_f = 0x0007001E,
        vmul_vs_f_i = 0x0007001F,
        vand_b = 0x00070020,
        vor_b = 0x00070021,
        vxor_b = 0x00070022,
        vnot_b = 0x00070023,
        vshl_i = 0x00070024,
        vshr_i = 0x00070025,
        vsar_i = 0x00070026,
        vshl_vs_i = 0x00070027,
        vcmp_eq_i = 0x00070028,
        vcmp_gt_i = 0x00070029,
        vcmp_lt_i = 0x0007002A,
        vcmp_eq_f = 0x0007002B,
        vcmp_gt_f = 0x0007002C,
        vcmp_lt_f = 0x0007002D,
        vblend_m = 0x0007002E,
        vload_m = 0x0007002F,
        vstore_m = 0x00070030,
        vshuffle = 0x00070031,
        vpack = 0x00070032,
        vunpack = 0x00070033,
        vreduce_add_i = 0x00070034,
        vreduce_mul_i = 0x00070035,
        vreduce_add_f = 0x00070036,
        vreduce_max_f = 0x00070037
    };

    enum class coreCalls : uint32_t
    {
        // RANDOM : 0x0008
        seed = 0x00080001,
        next_u32 = 0x00080002,
        next_u64 = 0x00080003,
        next_f32 = 0x00080004,
        next_f64 = 0x00080005,
        fill_bytes = 0x00080006,
        secure_fill_bytes = 0x00080007,

        // PRINT / DEBUG : 0x0009
        print_str = 0x00090001,
        print_i32 = 0x00090002,
        print_i64 = 0x00090003,
        print_f32 = 0x00090004,
        print_f64 = 0x00090005,
        flush = 0x00090006,

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
        wt_close = 0x13000008
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

    struct typeEntry
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
        uint32_t opCode;
        uint32_t op1, op2, op3;
    };

    struct alignas(64) binaryDesc
    {
        uint32_t magic; // 0x74694952 "tiIR"
        uint16_t versionMajor;
        uint16_t versionMinor;
        uint32_t flags;
        uint64_t binaryChecksum;
        uint32_t mainEntrypointIndex;

        uint32_t executableNameOffset;
        uint32_t executableNameCharCount; // ascii characters

        uint32_t capabilitiesOffset;
        uint32_t capabilitiesCount;

        uint32_t typesOffset;
        uint32_t typesCount;
        uint32_t typesPoolOffset;
        uint32_t typesPoolSize;

        uint32_t symbolsOffset;
        uint32_t symbolsCount;

        uint32_t dynamicLibsOffset;
        uint32_t dynamicLibsCount;

        uint32_t entrypointsOffset;
        uint32_t entrypointsCount;

        uint32_t functionsOffset;
        uint32_t functionsCount;

        uint32_t roDataOffset;
        uint32_t roDataCount;
        uint32_t roDataPoolOffset;
        uint32_t roDataPoolSize;

        uint32_t rwDataOffset;
        uint32_t rwDataCount;
        uint32_t rwDataPoolOffset;
        uint32_t rwDataPoolSize;

        uint32_t uninitializedDataSize;

        uint32_t instructionsOffset;
        uint32_t instructionsCount;
    };

    /*
    rules:
    - readonly datas are 64-byte aligned
    - readwrite datas are 64-byte aligned
    - uinitialized datas are 64-byte aligned
    */
    struct binary
    {
        header header;
        std::vector<capabilityEntry> capabilities;
        std::vector<typeEntry> types;
        std::vector<uint8_t> typesPool;
        std::vector<symbolEntry> symbols;
        std::vector<dynamicLibRef> dynamicLibs;
        std::vector<entrypoint> entrypoints;
        std::vector<functionEntry> functions;
        std::vector<dataEntry> readOnlyData;
        std::vector<uint8_t> readOnlyDataPool;
        std::vector<dataEntry> readWriteData;
        std::vector<uint8_t> readWriteDataPool;
        uint32_t readOnlyDataSize, readWriteDataSize, uninitializedDataSize;
        std::vector<instruction> instructions;
    };
};