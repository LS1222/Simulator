#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdlib.h>

#define MEMORY_SIZE 4096
#define REGISTER_DEFAULT 0
#define MEMORY_WORD_BTIS 20
#define MAX_MEM_LINE_LENGTH 5
typedef int unsigned Register;

typedef enum {
	REGISTER_ZERO,
	REGISTER_IMMIDIATE,
	REGISTER_RESULT_VALUE,
	REGISTER_ARGUMENT_0,
	REGISTER_ARGUMENT_1,
	REGISTER_ARGUMENT_2,
	REGISTER_ARGUMENT_3,
	REGISTER_TEMPORARY_0,
	REGISTER_TEMPORARY_1,
	REGISTER_TEMPORARY_2,
	REGISTER_SAVED_0,
	REGISTER_SAVED_1,
	REGISTER_SAVED_2,
	REGISTER_GLOBAL_POINTER,
	REGISTER_STACK_POINTER,
	REGISTER_RETURN_ADDRESS,
	REGISTER_PC,
	NUM_OF_REGISTERS
} RegisterOpcode;

typedef struct {
	Register irq0enable   : 1;
	Register irq1enable   : 1;
	Register irq2enable   : 1;
	Register irq0status   : 1;
	Register irq1status   : 1;
	Register irq2status   : 1;
	Register irqhandler   : 12;
	Register irqreturn    : 12;
	Register clks         : 32;
	Register leds         : 32;
	Register display7seg  : 32;
	Register timerenable  : 1;
	Register timercurrent : 32;
	Register timermax     : 32;
	Register diskcmd      : 2;
	Register disksector   : 7;
	Register diskbuffer   : 12;
	Register diskstatus   : 1;
	Register reserved[2];
	Register monitoraddr  : 16;
	Register monitordata  : 8;
	Register monitorcmd   : 1;
} IORegisters;

typedef struct {
	// Global Registers.
	Register* zero; // Constant to 0.
	Register* imm; // ?????
	Register* v0; // Result Value.
	Register* PC; // Program Counter register.

	// Argument Registers.
	Register* a0;
	Register* a1;
	Register* a2;
	Register* a3;

	// Temporary Registers.
	Register* t0;
	Register* t1;
	Register* t2;

	// Saved Registers.
	Register* s0;
	Register* s1;
	Register* s2;

	// Pointer Registers.
	Register* gp;
	Register* sp;
	Register* ra;

	// IORegisters io_regs; // Bonus.
} SimulatorRegisters;

typedef struct {
	int unsigned word : MEMORY_WORD_BTIS;
} MemoryWord;

typedef MemoryWord* SimulatorMemory;

#endif // _REGISTERS_H__
