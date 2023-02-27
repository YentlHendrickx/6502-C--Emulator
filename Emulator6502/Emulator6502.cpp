// Emulator6502.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "microMos6502.h"

microMos6502::microMos6502(BusRead r, BusWrite w) {
    
    Write = (BusWrite)w;
    Read = (BusRead);

    Instruct instr;

    // Fill jump table with illegal opcodes (on illegal opcode program ends)
    instr.addr = &microMos6502::IMP_Addr;
    instr.code = &microMos6502::Op_ILL;

    for (int i = 0; i < 256; i++) {
        InstructTable[i] = instr;
    }

    // Now the fun begins... add all opcodes
    // https://www.masswerk.at/6502/6502_instruction_set.html
    // Basically add adressing and operation to instruction with cycle count
    // Then store in instruction table

    /// ADC
    instr.code = &microMos6502::Op_ADC;

    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0x69] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x65] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x75] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x6D] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0x7D] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0x79] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0x61] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0x71] = instr;

    /// AND
    instr.code = &microMos6502::Op_AND;

    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0x29] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x25] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x35] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x2D] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0x3D] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0x39] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0x21] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0x31] = instr;


    /// ASL
    instr.code = &microMos6502::Op_ASL;

    instr.addr = &microMos6502::ACC_Addr;
    instr.cycles = 2;
    InstructTable[0x0A] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 5;
    InstructTable[0x06] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 6;
    InstructTable[0x16] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 6;
    InstructTable[0x0E] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 7;
    InstructTable[0x1E] = instr;

    /// BCC
    instr.code = &microMos6502::Op_BCC;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0x90] = instr;

    /// BCS
    instr.code = &microMos6502::Op_BCS;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0xB0] = instr;

    /// BEQ
    instr.code = &microMos6502::Op_BEQ;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0xF0] = instr;

    /// BIT
    instr.code = &microMos6502::Op_BIT;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x24] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x2C] = instr;

    /// BMI
    instr.code = &microMos6502::Op_BMI;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0x30] = instr;

    /// BNE
    instr.code = &microMos6502::Op_BNE;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0xD0] = instr;

    /// BPL
    instr.code = &microMos6502::Op_BPL;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0x10] = instr;

    /// BRK
    instr.code = &microMos6502::Op_BRK;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 7;
    InstructTable[0x00] = instr;

    /// BVC
    instr.code = &microMos6502::Op_BVC;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0x50] = instr;

    /// BVS
    instr.code = &microMos6502::Op_BVS;
    instr.addr = &microMos6502::REL_Addr;
    instr.cycles = 2;
    InstructTable[0x70] = instr;

    /// CLC
    instr.code = &microMos6502::Op_CLC;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x18] = instr;

    /// CLD
    instr.code = &microMos6502::Op_CLD;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xD8] = instr;

    /// CLI
    instr.code = &microMos6502::Op_CLI;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x58] = instr;

    /// CLV
    instr.code = &microMos6502::Op_CLV;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xB8] = instr;

    /// CMP
    instr.code = &microMos6502::Op_CMP;

    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xC9] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xC5] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0xD5] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xCD] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0xDD] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0xD9] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0xC1] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0xD1] = instr;

    /// CPX
    instr.code = &microMos6502::Op_CPX;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xE0] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xE4] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xEC] = instr;

    /// CPY
    instr.code = &microMos6502::Op_CPY;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xC0] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xC4] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xCC] = instr;

    /// DEC
    instr.code = &microMos6502::Op_DEC;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 5;
    InstructTable[0xC6] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 6;
    InstructTable[0xD6] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 6;
    InstructTable[0xCE] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 7;
    InstructTable[0xDE] = instr;

    /// DEX
    instr.code = &microMos6502::Op_DEX;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xCA] = instr;

    /// DEY
    instr.code = &microMos6502::Op_DEY;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x88] = instr;

    /// EOR
    instr.code = &microMos6502::Op_EOR;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0x49] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x45] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x55] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x4D] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0x5D] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0x59] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0x41] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0x51] = instr;

    /// INC
    instr.code = &microMos6502::Op_INC;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 5;
    InstructTable[0xE6] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 6;
    InstructTable[0xF6] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 6;
    InstructTable[0xEE] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 7;
    InstructTable[0xFE] = instr;

    /// INX
    instr.code = &microMos6502::Op_INX;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xE8] = instr;

    /// INY
    instr.code = &microMos6502::Op_INY;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xC8] = instr;


    /// JMP
    instr.code = &microMos6502::Op_JMP;
    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 3;
    InstructTable[0x4C] = instr;

    instr.addr = &microMos6502::ABI_Addr;
    instr.cycles = 5;
    InstructTable[0x6C] = instr;

    /// JSR
    instr.code = &microMos6502::Op_JSR;
    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 6;
    InstructTable[0x20] = instr;

    /// LDA
    instr.code = &microMos6502::Op_LDA;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xA9] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xA5] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0xB5] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xAD] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0xBD] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0xB9] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0xA1] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0xB1] = instr;

    /// LDX
    instr.code = &microMos6502::Op_LDX;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xA2] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xA6] = instr;

    instr.addr = &microMos6502::ZEY_Addr;
    instr.cycles = 4;
    InstructTable[0xB6] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xAE] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0xBE] = instr;

    /// LDY
    instr.code = &microMos6502::Op_LDY;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xA0] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xA4] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0xB4] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xAC] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0xBC] = instr;

    /// LSR
    instr.code = &microMos6502::Op_LSR;
    instr.addr = &microMos6502::ACC_Addr;
    instr.cycles = 2;
    InstructTable[0x4A] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 5;
    InstructTable[0x46] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 6;
    InstructTable[0x56] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 6;
    InstructTable[0x4E] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 7;
    InstructTable[0x5E] = instr;

    /// NOP
    instr.code = &microMos6502::Op_NOP;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xEA] = instr;

    /// ORA
    instr.code = &microMos6502::Op_ORA;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0x09] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x05] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x15] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x0D] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0x1D] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0x19] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0x01] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0x11] = instr;

    /// PHA
    instr.code = &microMos6502::Op_PHA;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 3;
    InstructTable[0x48] = instr;

    /// PHP
    instr.code = &microMos6502::Op_PHP;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 3;
    InstructTable[0x08] = instr;

    /// PLA
    instr.code = &microMos6502::Op_PLA;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 3;
    InstructTable[0x68] = instr;

    /// PLP
    instr.code = &microMos6502::Op_PLP;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 4;
    InstructTable[0x28];

    /// ROL
    instr.code = &microMos6502::Op_ROL;
    instr.addr = &microMos6502::ACC_Addr;
    instr.cycles = 2;
    InstructTable[0x2A] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 5;
    InstructTable[0x26] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 6;
    InstructTable[0x36] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 6;
    InstructTable[0x2E] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 7;
    InstructTable[0x3E] = instr;

    /// ROR
    instr.code = &microMos6502::Op_ROR;
    instr.addr = &microMos6502::ACC_Addr;
    instr.cycles = 2;
    InstructTable[0x6A] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 5;
    InstructTable[0x66] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 6;
    InstructTable[0x76] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 6;
    InstructTable[0x6E] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 7;
    InstructTable[0x7E] = instr;

    /// RTI
    instr.code = &microMos6502::Op_RTI;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 6;
    InstructTable[0x40] = instr;

    /// RTS
    instr.code = &microMos6502::Op_RTS;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 6;
    InstructTable[0x60];

    /// SBC
    instr.code = &microMos6502::Op_SBC;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xE9];

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xE5];

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0xF5];

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xED];

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0xFD];

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0xF9];

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0xE1];

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0xF1];

    /// SEC
    instr.code = &microMos6502::Op_SEC;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x38];

    /// SED
    instr.code = &microMos6502::Op_SED;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xF8];

    /// SEI
    instr.code = &microMos6502::Op_SEI;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x78];

    /// STA
    instr.code = &microMos6502::Op_STA;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x85];

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x95];

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x8D];

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 5;
    InstructTable[0x9D];

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 5;
    InstructTable[0x99];

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0x81];

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 6;
    InstructTable[0x91];

    /// STX
    instr.code = &microMos6502::Op_STX;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x86];

    instr.addr = &microMos6502::ZEY_Addr;
    instr.cycles = 4;
    InstructTable[0x96];

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x8E];

    /// STY
    instr.code = &microMos6502::Op_STY;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x84];

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x94];

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x8C];

    /// TAX
    instr.code = &microMos6502::Op_TAX;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xAA];

    /// TAY
    instr.code = &microMos6502::Op_TAY;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xA8];

    /// TSX
    instr.code = &microMos6502::Op_TSX;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xBA];

    /// TXA
    instr.code = &microMos6502::Op_TXA;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x8A];

    /// TXS
    instr.code = &microMos6502::Op_TXS;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x9A];

    /// TYA
    instr.code = &microMos6502::Op_TYA;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x98];
}


void microMos6502::Op_ADC() {
    bool carry = 0;

    //microMos6502::A + microMos6502::
}


int main()
{

    return 0;
}