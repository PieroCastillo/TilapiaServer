# Core Control Operations

CONTROL : 0x0000

| Operation Name | Mnemonic | Operand 1 | Operand 2 | Operand 3 | OpCode |
| --- | ---- | ---- | ---- | ---- | ---- |
| No Operation            | nop        | _ | _ | _  | 0x00000000 |
| Move                    | mov        | dstRg | srcRg | _  | 0x00000001 |
| Load i32 immediate      | li_i32     | dstRg | value | _  | 0x00000002 |
| Load u32 immediate      | li_u32     | dstRg | value | _  | 0x00000003 |
| Load f32 immediate      | li_f32     | dstRg | value | _  | 0x00000004 |
| Load 8 bytes immediate  | li64       | dstRg | higher 32 bits | lower 32 bits  | 0x00000005 |
| Load byte               | load_u8    | dstValueRg | srcAddressRg | srcOffsetRg | 0x00000006 |
| Load i16                | load_i16   | dstValueRg | srcAddressRg | srcOffsetRg | 0x00000007 |
| Load i32                | load_i32   | dstValueRg | srcAddressRg | srcOffsetRg | 0x00000008 |
| Load i64                | load_i64   | dstValueRg | srcAddressRg | srcOffsetRg | 0x00000009 |
| Load f32                | load_f32   | dstValueRg | srcAddressRg | srcOffsetRg | 0x0000000A |
| Load f64                | load_f64   | dstValueRg | srcAddressRg | srcOffsetRg | 0x0000000B |
| Store byte              | store_u8   | dstAddressRg | srcValueRg | dstOffsetRg | 0x0000000C |
| Store i16               | store_i16  | dstAddressRg | srcValueRg | dstOffsetRg | 0x0000000D |
| Store i32               | store_i32  | dstAddressRg | srcValueRg | dstOffsetRg | 0x0000000E |
| Store i64               | store_i64  | dstAddressRg | srcValueRg | dstOffsetRg | 0x0000000F |
| Store f32               | store_f32  | dstAddressRg | srcValueRg | dstOffsetRg | 0x00000010 |
| Store f64               | store_f64  | dstAddressRg | srcValueRg | dstOffsetRg | 0x00000011 |
| Call Function           | call       | funcID | firstRg | -      | 0x00000012 |
| Call Capability Func    | call_cap   | capID | funcID | firstRg  | 0x00000013 |
| Call Dynamic Lib Func   | call_lib   | libID | funcID | firstRg  | 0x00000014 |
| Return                  | ret        | _ | _ | _                 | 0x00000015 |
| Jump                    | jmp        | _ | _ | _                 | 0x00000016 |
| Branch if True          | br_true    | _ | _ | _                 | 0x00000017 |
| Branch if False         | br_false   | _ | _ | _                 | 0x00000018 |
| Branch Table            | br_table   | _ | _ | _                 | 0x00000019 |
| BSS Allocate            | alloc_bs   | dstPtrRg | offset   | size              | 0x0000001A |
| RO Allocate             | alloc_ro   | dstPtrRg | dataIdx  | _                 | 0x0000001B |
| RW Allocate             | alloc_rw   | dstPtrRg | dataIdx  | _                 | 0x0000001C |
| Heap Allocate           | alloc_hp   | dstPtrRg | sizeRg   | alignmentRg       | 0x0000001D |
| Free                    | free       | ptrRg | _ | _                           | 0x0000001E |
| Memory Copy             | memcpy     | dstAddressRg | srcAddressRg | sizeRg    | 0x0000001F |
| Memory Set              | memset     | dstPtrRg     | valueRg      | countRg   | 0x00000020 |
| Memory Move             | memmove    | dstPtrRg     | srcPtrRg     | sizeRg    | 0x00000021 |