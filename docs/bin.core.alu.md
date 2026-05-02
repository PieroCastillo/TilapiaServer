# Core ALU Operations

- ALU INT : 0x0001
- ALU FLOAT : 0x0002
- ALU BITWISE/LOGIC : 0x0003
- ALU COMP INT : 0x0004
- ALU COMP FLOAT : 0x0005

| Operation Name | Mnemonic | Operand 1 | Operand 2 | Operand 3 | OpCode |
| --- | ---- | ---- | ---- | ---- | ---- |
| Integer ALU  | | | | | |
| Add          | add_i    |   dstRg | src1Rg | src2Rg    | 0x00010001 |
| Substract    | sub_i    |   dstRg | src1Rg | src2Rg    | 0x00010002 |
| Multiplicate | mul_i    |   dstRg | src1Rg | src2Rg    | 0x00010003 |
| Divide       | div_i    |   dstRg | src1Rg | src2Rg    | 0x00010004 |
| Module       | mod_i    |   dstRg | src1Rg | src2Rg    | 0x00010005 |
| Float ALU    | | | | | |
| Add          | add_f    |   dstRg | src1Rg | src2Rg    | 0x00020001 |
| Substract    | sub_f    |   dstRg | src1Rg | src2Rg    | 0x00020002 |
| Multiplicate | mul_f    |   dstRg | src1Rg | src2Rg    | 0x00020003 |
| Divide       | div_f    |   dstRg | src1Rg | src2Rg    | 0x00020004 |
| Bitwise/Logic   | | | | | |
| And          | and_b    |   dstRg | src1Rg | src2Rg    | 0x00030001 |
| Or           | or_b     |   dstRg | src1Rg | src2Rg    | 0x00030002 |
| Exclusive Or | xor_b    |   dstRg | src1Rg | src2Rg    | 0x00030003 |
| Not          | not_b    |   dstRg | srcRg  | _         | 0x00030004 |
| Left Shift   | shl_b    |   dstRg | src1Rg | src2Rg    | 0x00030005 |
| Right Shift  | shr_b    |   dstRg | src1Rg | src2Rg    | 0x00030006 |
| Integer Compare | | | | | |
| Equal        | cmp_eq_i |   dstRg | src1Rg | src2Rg    | 0x00040001 |
| Not Equal    | cmp_ne_i |   dstRg | src1Rg | src2Rg    | 0x00040002 |
| Less Than    | cmp_lt_i |   dstRg | src1Rg | src2Rg    | 0x00040003 |
| Greater Than | cmp_gt_i |   dstRg | src1Rg | src2Rg    | 0x00040004 |
| Float Compare   | | | | | |
| Equal        | cmp_eq_f |   dstRg | src1Rg | src2Rg    | 0x00050001 |
| Less Than    | cmp_lt_f |   dstRg | src1Rg | src2Rg    | 0x00050002 |
| Greater Than | cmp_gt_f |   dstRg | src1Rg | src2Rg    | 0x00050003 |