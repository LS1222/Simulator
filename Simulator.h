#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "GlobalDefines.h"
#include "Formats.h"
#include "Registers.h"

// Defines.
#define MAX_FILENAME_SIZE 30

// Enums.
typedef enum {
	READ,
	WRITE,
	READ_BIN,
	WRITE_BIN,
	NONE
} AccessEnum;

// Structs.
typedef struct {
	char       name[MAX_FILENAME_SIZE];
	int        name_length;
	FILE* handle;
	AccessEnum access;
} SimFile;

typedef struct {
	SimFile* memin;
	SimFile* memout;
	SimFile* regout;
	SimFile* trace;
	SimFile* cycles;
} SimulatorFiles;

typedef struct {
	// Memories.
	SimulatorFiles files;
	// SimulatorRegisters regs; TODO: Remove.
	Register regs[NUM_OF_REGISTERS];
	SimulatorMemory mem;

	// Global variables.
	int unsigned cycles;
	ErrorCode status;

	// Fetch-Decode-Execute variables.
	MemoryWord lines[2];
	OpcodeType command_type;
	CommandFormat command;
} Simulator;

#endif // __SIMULATOR_H__
