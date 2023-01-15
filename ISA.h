#ifndef __ISA_H__
#define __ISA_H__

#include "GlobalDefines.h"
#include "Simulator.h"

typedef enum {
	ADD = 0,
	SUB,
	MUL,
	AND,
	OR,
	XOR,
	SLL,
	SRA,
	SRL,
	BEQ,
	BNE,
	BLT,
	BGT,
	BLE,
	BGE,
	JAL,
	LW,
	SW,
	HALT,
	NUM_OF_OPCODES
} OpcodeCommand;

// Function Prototypes.
void add(Simulator* sim);
void sub(Simulator* sim);
void mul(Simulator* sim);
void and(Simulator* sim);
void or (Simulator* sim);
void xor(Simulator* sim);
void sll(Simulator* sim);
void sra(Simulator* sim);
void srl(Simulator* sim);
void beq(Simulator* sim);
void bne(Simulator* sim);
void blt(Simulator* sim);
void bgt(Simulator* sim);
void ble(Simulator* sim);
void bge(Simulator* sim);
void jal(Simulator* sim);
void lw (Simulator* sim);
void sw (Simulator* sim);

// Define a function signature
typedef void (*opcode_function) (Simulator* sim);
static const opcode_function opcode_functions[NUM_OF_OPCODES] = { add, sub, mul, and, or, xor, sll, sra, srl, beq, bne, blt, bgt, ble, bge, jal, lw, sw };

#endif // __ISA_H__