# Core Print Calls      
      
PRINT / DEBUG : 0x0009


| Call Name | Call Mnemonic | OpCode | Params | 
|:--:| - | - | - | 
| Print string   | print_str | 0x00090001 | strPtrRg |
| Print int 32   | print_i32 | 0x00090002 | valueRg  |
| Print int 64   | print_i64 | 0x00090003 | valueRg  |
| Print float 64 | print_f32 | 0x00090004 | valueRg  |
| Print float 64 | print_f64 | 0x00090005 | valueRg  |
| Flush Output   | flush     | 0x00090006 | valueRg  |