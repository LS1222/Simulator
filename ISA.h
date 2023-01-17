#ifndef __ISA_H__
#define __ISA_H__

/*===================================
|           INCLUDES                |
====================================*/
#include "Global.h"
#include "Simulator.h"

/*===================================
|             MACROS                |
====================================*/
#define REGS_IMM_ASSIGN(REG) \
	Register* REG = NULL; \
	do { \
		REG = &sim->regs[sim->command.REG]; \
		if (REGISTER_IMMIDIATE == sim->command.REG) { *REG = sim->command.imm; } \
	} while (0)

/*===================================
|            ENUMS                  |
====================================*/
typedef enum {
	OPCODE_ADD = 0,
	OPCODE_SUB,
	OPCODE_MUL,
	OPCODE_AND,
	OPCODE_OR,
	OPCODE_XOR,
	OPCODE_SLL,
	OPCODE_SRA,
	OPCODE_SRL,
	OPCODE_BEQ,
	OPCODE_BNE,
	OPCODE_BLT,
	OPCODE_BGT,
	OPCODE_BLE,
	OPCODE_BGE,
	OPCODE_JAL,
	OPCODE_LW,
	OPCODE_SW,
	OPCODE_RETI,
	OPCODE_IN,
	OPCODE_OUT,
	OPCODE_HALT,
	NUM_OF_OPCODES
} OpcodeCommand;

/*===================================
|        FUNCTIONS PROTOTYPE        |
====================================*/
void add (Simulator* sim);
void sub (Simulator* sim);
void mul (Simulator* sim);
void and (Simulator* sim);
void or  (Simulator* sim);
void xor (Simulator* sim);
void sll (Simulator* sim);
void sra (Simulator* sim);
void srl (Simulator* sim);
void beq (Simulator* sim);
void bne (Simulator* sim);
void blt (Simulator* sim);
void bgt (Simulator* sim);
void ble (Simulator* sim);
void bge (Simulator* sim);
void jal (Simulator* sim);
void lw  (Simulator* sim);
void sw  (Simulator* sim);
void reti(Simulator* sim);
void in  (Simulator* sim);
void out (Simulator* sim);
void halt(Simulator* sim);

// Define a function signature
typedef void (*opcode_function) (Simulator* sim);
static const opcode_function opcode_functions[NUM_OF_OPCODES] = { add, sub, mul, and, or, xor, sll, sra, srl, beq, bne, blt, bgt, ble, bge, jal, lw, sw, reti, in, out, halt };

#endif // __ISA_H__