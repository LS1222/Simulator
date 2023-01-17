#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

/*===================================
|           INCLUDES                |
====================================*/
#include "Global.h"
#include "Monitor.h"
#include "Memory.h"

/*===================================
|            STRUCTS                |
====================================*/
typedef struct {
	int unsigned rt : 4;
	int unsigned rs : 4;
	int unsigned rd : 4;
	int unsigned opcode : 8;
	int unsigned imm : 20;
} CommandFormat;

typedef struct {
	// Memories.
	SimulatorFiles    files;
	SimulatorMemory   mem;
	SimulatorMonitor  monitor;
	SimulatorHardDisk hdsk;
	Register          regs   [NUM_OF_REGISTERS];
	IORegister        io_regs[NUM_OF_IO_REGISTERS];
	

	// Global variables.
	int unsigned cycles;
	ErrorCode    status;

	// Fetch-Decode-Execute variables.
	MemoryWord    lines[2];
	CommandFormat command;
	bool          irq0;
	bool          irq1;
	bool          irq2;
	bool          isr_mode;
} Simulator;

#endif // __SIMULATOR_H__