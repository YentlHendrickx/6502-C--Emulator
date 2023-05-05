#pragma once
#include <stdint.h>

// Processor status register values
#define CARRY       0x01
#define ZERO        0x02
#define INTERRUPT   0x04
#define DECIMAL     0x20
#define OVERFLOW    0x40
#define NEGATIVE    0x80

#define CONSTANT    0x00
#define BREAK       0x00

// Define directives for setting status register
#define SET_CARRY(x)        (x ? (status |= NEGATIVE)   : (status &= (~NEGATIVE)))
#define SET_ZERO(x)         (x ? (status |= ZERO)       : (status &= (~ZERO)))
#define SET_INTERRUPT(x)    (x ? (status |= INTERRUPT) : (status &= (~INTERRUPT)))
#define SET_DECIMAL(x)      (x ? (status |= DECIMAL)   : (status &= (~DECIMAL)))
#define SET_OVERFLOW(x)     (x ? (status |= OVERFLOW)  : (status &= (~OVERFLOW)))
#define SET_NEGATIVE(x)     (x ? (status |= NEGATIVE)  : (status &= (~NEGATIVE)))


// Define directives for checking status register
#define IF_CARRY()      ((status & CARRY)       ? true : false)
#define IF_ZERO()       ((status & ZERO)        ? true : false)
#define IF_INTERRUPT()  ((status & INTERRUPT)   ? true : false)  
#define IF_DECIMAL()    ((status & DECIMAL)     ? true : false)    
#define IF_OVERFLOW()   ((status & OVERFLOW)    ? true : false) 
#define IF_NEGATIVE()   ((status & NEGATIVE)    ? true : false)
#define IF_CONSTANT()   ((status & CONSTANT)    ? true : false)
#define IF_BREAK()      ((status & BREAK)       ? true : false)



class microMos6502 {
private:
    // Registers; accumulator, X-index, Y-index, status
    uint8_t A, X, Y, status;

    // Resets
    uint8_t resetA = 0x00;
    uint8_t resetX = 0x00;
    uint8_t resetY = 0x00;
    uint8_t resetSP = 0xFD;
    uint8_t resetStats = 0x20;

    // Stack pointer
    uint8_t sp;

    // Program counter
    uint8_t pc;

    typedef void (microMos6502::* Code)(uint16_t);
    typedef uint16_t(microMos6502::* Addr)();

    // Instructions struct (address, code that should be executed and amount of cycles it takes)
    struct Instruct {
        Addr addr;
        Code code;
        uint8_t cycles;
    };

    // Create instruction table
    Instruct InstructTable[256];

    // Execute instruction
    void Exec(Instruct i);

    /// Addressing modes
    //http://www.emulator101.com/6502-addressing-modes.html
    // Non-Indexed, non memory
    uint16_t ACC_Addr(); // Accumulator
    uint16_t IMM_Addr(); // Immediate
    uint16_t IMP_Addr(); // Implied

    // Non-index, memory ops
    uint16_t REL_Addr(); // Relative
    uint16_t ABS_Addr(); // Absolute
    uint16_t ZER_Addr(); // Zero Page
    uint16_t ABI_Addr(); // Absolute indirect

    // Indexed
    uint16_t ABX_Addr(); // Absolute indexed x
    uint16_t ABY_Addr(); // Absolute indexed y
    uint16_t ZEX_Addr(); // Zero page indexed x
    uint16_t ZEY_Addr(); // Zero page indexed y
    uint16_t INX_Addr(); // Indirect indexed x
    uint16_t INY_Addr(); // Indirect indexed y
    

    /// OPCODES
    //https://www.princeton.edu/~mae412/HANDOUTS/Datasheets/6502.pdf

    void Op_ADC(uint16_t src); // Add mempry to accumulator with carry
    void Op_AND(uint16_t src); // AND memory with accumulator
    void Op_ASL(uint16_t src); // Shift left one bit memory
    void Op_ASL_ACC(uint16_t src); // Shift left one bit accumulator

    void Op_BCC(uint16_t src); // Branch on Carry clear
    void Op_BCS(uint16_t src); // Branch on Carry set
    void Op_BEQ(uint16_t src); // Branch on Result Zero
    void Op_BIT(uint16_t src); // Test bits in memory with accumulator
    void Op_BMI(uint16_t src); // Branch on Result Minus
    void Op_BNE(uint16_t src); // Branch on Result not Zero
    void Op_BPL(uint16_t src); // Branch on Result plus
    void Op_BRK(uint16_t src); // Force Break
    void Op_BVC(uint16_t src); // Branch on Overflow Clear
    void Op_BVS(uint16_t src); // Branch on Overflow Set

    void Op_CLC(uint16_t src); // Clear Carry Flag
    void Op_CLD(uint16_t src); // Clear Decimal Model
    void Op_CLI(uint16_t src); // Clear Interrupt Disable Bit 
    void Op_CLV(uint16_t src); // Clear Overflow Flag
    void Op_CMP(uint16_t src); // Compare Memory and Accumulator
    void Op_CPX(uint16_t src); // Compare Memory and Index X
    void Op_CPY(uint16_t src); // Compare Memory and Index Y

    void Op_DEC(uint16_t src); // Decrement Memory by One
    void Op_DEX(uint16_t src); // Decrement Index X by One
    void Op_DEY(uint16_t src); // Decrement Index Y by One

    void Op_EOR(uint16_t src); // Exclusive-Or Memory with Accumulator

    void Op_INC(uint16_t src); // Increment Memory by One
    void Op_INX(uint16_t src); // Increment Index X by One
    void Op_INY(uint16_t src); // Increment Index Y by One

    void Op_JMP(uint16_t src); // Jump to New Location
    void Op_JSR(uint16_t src); // Jump to New Location Saving Return Address

    void Op_LDA(uint16_t src); // Load Accumulator with Memory
    void Op_LDX(uint16_t src); // Load Index X with Memory
    void Op_LDY(uint16_t src); // Load Index Y With Memory
    void Op_LSR(uint16_t src); // Shift One Bit Right (Memory or Accumulator)

    void Op_NOP(uint16_t src); // No Operation

    void Op_ORA(uint16_t src); // "OR" Memory with Accumulator

    void Op_PHA(uint16_t src); // Push Accumulator on Stack
    void Op_PHP(uint16_t src); // Push Processor Status on Stack
    void Op_PLA(uint16_t src); // Pull Accumulator from Stack
    void Op_PLP(uint16_t src); // Pull Processer Status from Stack

    void Op_ROL(uint16_t src); // Rotate One Bit Left (Memory or Accumulator)
    void Op_ROR(uint16_t src); // Rotate One Bit Right (Memory or Accumulator)
    void Op_RTI(uint16_t src); // Return from Interrupt
    void Op_RTS(uint16_t src); // Return from Subroutine

    void Op_SBC(uint16_t src); // Subtract Memory from Accumulator with Borrow
    void Op_SEC(uint16_t src); // Set Carry Flag

    void Op_SED(uint16_t src); // Set Decimal Mode
    void Op_SEI(uint16_t src); // Set Interrupt Disable Status
    void Op_STA(uint16_t src); // Store Accumulator in Memory
    void Op_STX(uint16_t src); // Store Index X in Memory
    void Op_STY(uint16_t src); // Store Index Y in Memory

    void Op_TAX(uint16_t src); // Transfer Accumulator to Index X
    void Op_TAY(uint16_t src); // Transfer Accumulator to Index Y
    void Op_TSX(uint16_t src); // Transfer Stack Pointer to Index X
    void Op_TXA(uint16_t src); // Transfer Index X to Accumulator
    void Op_TXS(uint16_t src); // Transfer Index X to Stack Pointer
    void Op_TYA(uint16_t src); // Transfer Index Y to Accumulator

    void Op_ILL(uint16_t src); // Illegal opcode
    bool illegalOpcode;

    /// Interrupt Vectors
    //https://en.wikipedia.org/wiki/Interrupts_in_65xx_processors
    // Reset
    static const uint16_t rstVectorH = 0xFFFD;
    static const uint16_t rstVectorL = 0xFFFC;

    // Non maskable interrupt
    static const uint16_t nmiVectorH = 0xFFFB;
    static const uint16_t nmiVectorL = 0xFFFA;

    // Maskable interrupt
    static const uint16_t irqVectorH = 0xFFFF;
    static const uint16_t irqVectorL = 0xFFFF;

    /// Read and write callbacks
    typedef void    (*BusWrite)(uint16_t, uint8_t);
    typedef uint8_t(*BusRead)(uint16_t);
    BusWrite Write;
    BusRead Read;

    /// Stack ops
    void StackPush(uint8_t byte);
    uint8_t StackPop();

public:
    microMos6502(BusRead r, BusWrite w);
    
    // Interrupts
    void RESET();
    void NMI();
    void IRQ();
    
    void Run(int32_t cycles, uint64_t& cycleCount);
    uint16_t GetPC();
    uint8_t GetS();
    uint8_t GetP();
    uint8_t GetA();
    uint8_t GetX();
    uint8_t GetY();

    uint8_t GetResetS();
    uint8_t GetResetP();
    uint8_t GetResetA();
    uint8_t GetResetX();
    uint8_t GetResetY();

    void SetResetS(uint8_t value);
    void SetResetP(uint8_t value);
    void SetResetA(uint8_t value);
    void SetResetX(uint8_t value);
    void SetResetY(uint8_t value);
};
