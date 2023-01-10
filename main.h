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
#define CHECK_FILE_STATUS(ACTUAL, EXP_NAME) { \
	status = checkCLIfile(ACTUAL, EXP_NAME); \
	if (status != NO_ERROR) { return (status); } \
}

#define SIMFILE_OPEN(HANDLE, ARG, NAME, ACCESS) { \
	CHECK_FILE_STATUS(ARG, NAME); \
	strcpy(HANDLE->name,  ARG); \
	HANDLE->name_length = strlen(HANDLE->name); \
	switch (ACCESS) { \
		case (READ):  HANDLE->handle = fopen(HANDLE->name, "r"); break; \
		case (WRITE): HANDLE->handle = fopen(HANDLE->name, "w"); break; \
	} \
}

// Funciton prototypes.
ErrorCode checkCLIfile(char* act_name, const char* exp_name);
ErrorCode ParseCLI(int argc, char* argv[], SimulatorFiles* files);
void InitializeRegisters(GlobalRegisters* regs);

#endif // __MAIN_H__
