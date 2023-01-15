#ifndef __GLOBAL_DEFINES_H__
#define __GLOBAL_DEFINES_H__

#include <stdlib.h>
#include <stdio.h>

/*===================================
|         INPUT FILES               |
====================================*/
#define RAM_INPUT_FILE "memin.txt"
#define HDISK_INPUT_FILE "diskin.txt"
#define EXTERNAL_INT_FILE "irq2in.txt"

/*===================================
|         OUTPUT FILES              |
====================================*/
#define RAM_OUTPUT_FILE "memout.txt"
#define REGISTER_OUTPUT_FILE "regout.txt"
#define TRACE_OUTPUT_FILE "trace.txt" // Trace print format: PC INTS R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15
#define HW_REGISTERS_OUTPUT_FILE "hwregtrace.txt"
#define CYCLE_OUTPUT_FILE "cycles.txt"
#define LEDS_OUTPUT_FILE "leds.txt"
#define SEGMENT_DISPLAY_OUTPUT_FILE "display7seg.txt"
#define HDISK_OUTPUT_FILE "diskout.txt"
#define MONITOR_OUTPUT_FILE "monitor.txt"
#define MONITOR_YUV_OUTPUT_FILE "monitor.yuv"

/*===================================
|          ERROR CODES               |
====================================*/
typedef enum {
	NO_ERROR = 0,
	INCORRECT_CLI_ARGUMENTS,
	INPUT_FILE_DOES_NOT_EXISTS,
	FILE_BAD_NAME,
	FILE_BAD_EXTENSION,
	MEMORY_ALLOCATION_ERROR,
	MEM_EOF,
	FILE_CLOSED,
	BAD_COMMAND_FORMAT,
	HALT_SIMULATOR,
	NUM_OF_ERRORS
} ErrorCode;

// Macros.
#define SIMFILE_INIT(SIMFILE, SIMULATOR) { \
	SIMFILE = (SimFile*)malloc(sizeof(SimFile)); \
	if (NULL == SIMFILE) { \
		SIMULATOR->status = MEMORY_ALLOCATION_ERROR; \
		return; \
	} \
	SIMFILE->name_length = 0; \
	for (int i = 0; i < MAX_FILENAME_SIZE; i++) { \
		SIMFILE->name[i] = '\0'; \
	} };

#define CHECK_FILE_STATUS(ACTUAL, EXP_NAME, SIMULATOR) { \
	checkCLIfile(ACTUAL, EXP_NAME, SIMULATOR); \
	if (SIMULATOR->status != NO_ERROR) { return; } \
}

#define SIMFILE_OPEN(HANDLE, ARG, NAME, ACCESS, SIMULATOR) { \
	CHECK_FILE_STATUS(ARG, NAME, SIMULATOR); \
	strcpy(HANDLE->name,  ARG); \
	HANDLE->name_length = strlen(HANDLE->name); \
	switch (ACCESS) { \
		case (READ):      HANDLE->handle = fopen(HANDLE->name, "r");  break; \
		case (WRITE):     HANDLE->handle = fopen(HANDLE->name, "w");  break; \
		case (READ_BIN):  HANDLE->handle = fopen(HANDLE->name, "rb"); break; \
		case (WRITE_BIN): HANDLE->handle = fopen(HANDLE->name, "wb"); break; \
	} \
}

#define STR_(X) #X
#define STR(X) STR_(X)

#define CLOSE_FILE(HANDLE, SIMULATOR) { \
	if (feof(HANDLE)) { \
		SIMULATOR->status |= FILE_CLOSED; \
	} else { \
		fclose(HANDLE); \
		HANDLE = NULL; \
	} };

#endif // __GLOBAL_DEFINES_H__