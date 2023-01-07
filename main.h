#ifndef __MAIN_H__
#define __MAIN_H__

// Defines.
#define _CRT_SECURE_NO_WARNINGS

// Include libraries.
#include <stdio.h>
#include "GlobalDefines.h"
#include "Loop.h"
#include "Registers.h"

// Macros.
#define CHECK_FILE_RETURN_STATUS(ACTUAL, EXP_NAME, EXP_EXT) { \
	status = checkCLIfile(ACTUAL, EXP_NAME, EXP_EXT); \
	if (status != NO_ERROR) { return (status); } \
}

// Structs.
typedef struct {
	char* memin;
	char* memout;
	char* regout;
	char* trace;
	char* cycles;
} SimulatorFiles;

// Funciton prototypes.
ErrorCode checkCLIfile(char* act_name, const char* exp_name, const char* exp_extention);
ErrorCode ParseCLI(int argc, char* argv[], SimulatorFiles* file_names);
void InitializeRegisters(GlobalRegisters* regs);

#endif // __MAIN_H__
