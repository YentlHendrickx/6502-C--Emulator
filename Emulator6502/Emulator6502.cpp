// Emulator6502.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "microMos6502.h"

microMos6502::microMos6502(BusRead r, BusWrite w) {
    
    Write = (BusWrite)w;
    Read = (BusRead)r;

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
    InstructTable[0x28] = instr;

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
    InstructTable[0x60] = instr;

    /// SBC
    instr.code = &microMos6502::Op_SBC;
    instr.addr = &microMos6502::IMM_Addr;
    instr.cycles = 2;
    InstructTable[0xE9] = instr;

    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0xE5] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0xF5] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0xED] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 4;
    InstructTable[0xFD] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 4;
    InstructTable[0xF9] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0xE1] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 5;
    InstructTable[0xF1] = instr;

    /// SEC
    instr.code = &microMos6502::Op_SEC;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x38] = instr;

    /// SED
    instr.code = &microMos6502::Op_SED;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xF8] = instr;

    /// SEI
    instr.code = &microMos6502::Op_SEI;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x78] = instr;

    /// STA
    instr.code = &microMos6502::Op_STA;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x85] = instr; 

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x95] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x8D] = instr;

    instr.addr = &microMos6502::ABX_Addr;
    instr.cycles = 5;
    InstructTable[0x9D] = instr;

    instr.addr = &microMos6502::ABY_Addr;
    instr.cycles = 5;
    InstructTable[0x99] = instr;

    instr.addr = &microMos6502::INX_Addr;
    instr.cycles = 6;
    InstructTable[0x81] = instr;

    instr.addr = &microMos6502::INY_Addr;
    instr.cycles = 6;
    InstructTable[0x91] = instr;

    /// STX
    instr.code = &microMos6502::Op_STX;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x86] = instr;

    instr.addr = &microMos6502::ZEY_Addr;
    instr.cycles = 4;
    InstructTable[0x96] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x8E] = instr;

    /// STY
    instr.code = &microMos6502::Op_STY;
    instr.addr = &microMos6502::ZER_Addr;
    instr.cycles = 3;
    InstructTable[0x84] = instr;

    instr.addr = &microMos6502::ZEX_Addr;
    instr.cycles = 4;
    InstructTable[0x94] = instr;

    instr.addr = &microMos6502::ABS_Addr;
    instr.cycles = 4;
    InstructTable[0x8C] = instr;

    /// TAX
    instr.code = &microMos6502::Op_TAX;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xAA] = instr;

    /// TAY
    instr.code = &microMos6502::Op_TAY;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xA8] = instr;

    /// TSX
    instr.code = &microMos6502::Op_TSX;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0xBA] = instr;

    /// TXA
    instr.code = &microMos6502::Op_TXA;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x8A] = instr;

    /// TXS
    instr.code = &microMos6502::Op_TXS;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x9A] = instr;

    /// TYA
    instr.code = &microMos6502::Op_TYA;
    instr.addr = &microMos6502::IMP_Addr;
    instr.cycles = 2;
    InstructTable[0x98] = instr;
}

/// MEMORY IMPLEMENTATION
uint16_t microMos6502::ACC_Addr() {
    // Not in use
    return -1;
}

// Immediate addres -> progam counter
uint16_t microMos6502::IMM_Addr() {
    return pc++;
}

// Absolute addres, read pc counter get both low and high addres -> return address
uint16_t microMos6502::ABS_Addr() {
    uint16_t lowByte, highByte;

    lowByte = Read(pc++);
    highByte = Read(pc++);

    return (lowByte + (highByte << 8));
}

// Zero addres -> get address at pc
uint16_t microMos6502::ZER_Addr() {
    return Read(pc++);
}

// Implied addres -> not in use
uint16_t microMos6502::IMP_Addr() {
    return 0;
}

// Relative address
uint16_t microMos6502::REL_Addr() {
    uint16_t offset;

    // Get offset from pc counter, apply offset if needed
    offset = (uint16_t)Read(pc++);
    if (offset & 0x80) offset |= 0xFF00;
    
    return (pc + (int16_t)offset);
}

/// STACK IMPLEMENTATION

// Push to stack, 6502 has reverse stack so stack pointer will be decremented
void microMos6502::StackPush(uint8_t byte) {
    Write(0x0100 + sp, byte);

    // Wrap stack pointer if underflow
    if (sp == 0x00) {
        sp = 0xFF;
    }
    else {
        sp--;
    }
}

// Pop from stack, 6502 has reverse stack so stack pointer will be incremented
uint8_t microMos6502::StackPop() {
    // Catch stack overflow
    if (sp == 0xFF) {
        // Wrap pointer
        sp = 0x00;
    }
    else {
        sp++;
    }

    // Return byte at current sp
    return Read(0x0100 + sp);
}

/// OP CODE IMPLEMENTATIONS

// ADC, Add Memory to Accumulator with Carry
void microMos6502::Op_ADC(uint16_t src)
{
    uint8_t m = Read(src);

    // Add and add current carry flag
    unsigned int tmp = m + A + (IF_CARRY() ? 1 : 0);
    
    SET_ZERO((tmp & 0xFF));

    // If decimal, set carry
    if (IF_DECIMAL()) {
        // In decimal mode operation uses BCD
        if (((A & 0xF) + (m & 0xF) + (IF_CARRY() ? 1 : 0)) > 9) tmp += 6;
        SET_NEGATIVE(tmp & 0x80);
        SET_OVERFLOW(!((A ^ m) & 0x80) && ((A ^ tmp) & 0x80));

        // for BCD
        if (tmp > 0x99) {
            tmp += 96;
        }

        SET_CARRY(tmp > 0x99);
    } else {
        // Set flags
        SET_NEGATIVE(tmp & 0x80);
        SET_OVERFLOW(!((A ^ m) & 0x80) && ((A ^ tmp) & 0x80));
        SET_CARRY(tmp > 0xFF);
    }

    // Finally store mem to accumulator address
    A = tmp & 0xFF;
    return;
}

// AND, memory with accumulator
void microMos6502::Op_AND(uint16_t src) {
    // Get memory from location
    uint16_t m = Read(src);

    // Perform AND
    uint8_t res = m & A;

    // Set negative and zero flags
    SET_NEGATIVE(res & 0x80);
    SET_ZERO(!res);

    return;
}

// ASL, shift left one bit
void microMos6502::Op_ASL(uint16_t src) {
    // Get mem from location
    uint8_t m = Read(src);

    // Set carry flags in status
    SET_CARRY(m & 0x80);

    // Shift, fill in low nibble
    m <<= 1;
    m &= 0xFF;

    // Set flags
    SET_NEGATIVE(m & 0x80);
    SET_ZERO(!m);

    // Write result to mem
    Write(src, m);
    return;
}

// Same as standard ASL but for ACC register
void microMos6502::Op_ASL_ACC(uint16_t src) {

    uint8_t m = A;

    // Set carry flags in status
    SET_CARRY(m & 0x80);

    // Shift, fill low nibble
    m <<= 1;
    m &= 0xFF;

    // Set flags
    SET_NEGATIVE(m & 0x80);
    SET_ZERO(!m);

    A = m;
    return;
}

// BCC, branch on carry clear
void microMos6502::Op_BCC(uint16_t src) {
    // Set program counter to src -> jump
    if (!IF_CARRY()) {
        pc = src;
    }

    return;
}

// BCS, Branch on carry set
void microMos6502::Op_BCS(uint16_t src) {
    // Set program counter to src -> jump
    if (IF_CARRY()) {
        pc = src;
    }
    return;
}

// BEQ, Branch on result zero
void microMos6502::Op_BEQ(uint16_t src) {
    // Set program counter to src -> jump
    if (IF_ZERO()) {
        pc = src;
    }
    return;
}

// BIT, Test bits in memory with accumulator ???
void microMos6502::Op_BIT(uint16_t src) {
    return;
}

// BMI, Branch on result minus
void microMos6502::Op_BMI(uint16_t src) {
    if (IF_NEGATIVE()) {
        pc = src;
    }
    return;
}

// BNE, Branch on result not zero
void microMos6502::Op_BNE(uint16_t src) {
    if (!IF_ZERO()) {
        pc = src;
    }
    return;
}

// BPL, Branch on result plus
void microMos6502::Op_BPL(uint16_t src) {
    if (!IF_NEGATIVE()) {
        pc = src;
    }
    return;
}

// BRK, Force break
void microMos6502::Op_BRK(uint16_t src) {

    pc++;
    StackPush((pc >> 8) & 0xFF);
    StackPush(pc & 0xFF);
    StackPush(status | CONSTANT | BREAK);
    SET_INTERRUPT(1);
    pc = (Read(irqVectorH) << 8) + Read(irqVectorL);

    return;
}

// BVC, Branch on overflow clear
void microMos6502::Op_BVC(uint16_t src) {
    if (!IF_OVERFLOW()) {
        pc = src;
    }
    return;
}

// BVS, Branch on overflow set
void microMos6502::Op_BVS(uint16_t src) {
    if (IF_OVERFLOW()) {
        pc = src;
    }
    return;
}

// CLC, Clear carry flag
void microMos6502::Op_CLC(uint16_t src) {
    SET_CARRY(0);
    return;
}

// CLD, clear decimal mode
void microMos6502::Op_CLD(uint16_t src) {
    SET_DECIMAL(0);
    return;
}

// CLI, clear intterupt disable bit
void microMos6502::Op_CLI(uint16_t src) {
    SET_INTERRUPT(0);
    return;
}

// CLV, clear overflow flag
void microMos6502::Op_CLV(uint16_t src) {
    SET_OVERFLOW(0);
    return;
}


int main()
{

    return 0;
}
