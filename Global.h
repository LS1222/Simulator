#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/*===================================
|           INCLUDES                |
====================================*/
#include <stdlib.h>
#include <stdio.h>

/*===================================
|           DEFINES                 |
====================================*/
#define MAX_FILENAME_SIZE 50
#define NUM_OF_CLI_ARGS   12

// Input Files.
#define RAM_INPUT_FILE "memin.txt"
#define HDISK_INPUT_FILE "diskin.txt"
#define EXTERNAL_INT_FILE "irq2in.txt"

// Output Files.
#define RAM_OUTPUT_FILE "memout.txt"
#define REGISTER_OUTPUT_FILE "regout.txt"
#define TRACE_OUTPUT_FILE "trace.txt"
#define HW_REGISTERS_OUTPUT_FILE "hwregtrace.txt"
#define CYCLE_OUTPUT_FILE "cycles.txt"
#define LEDS_OUTPUT_FILE "leds.txt"
#define SEGMENT_DISPLAY_OUTPUT_FILE "display7seg.txt"
#define HDISK_OUTPUT_FILE "diskout.txt"
#define MONITOR_OUTPUT_FILE "monitor.txt"
#define MONITOR_YUV_OUTPUT_FILE "monitor.yuv"

/*===================================
|             MACROS                |
====================================*/
#define STR_(X) #X
#define STR(X) STR_(X)

#define SIMFILE_INIT(SIMFILE, SIMULATOR) \
	do { \
		SIMFILE = (SimFile*)malloc(sizeof(SimFile)); \
		if (NULL == SIMFILE) { SIMULATOR->status = MEMORY_ALLOCATION_ERROR; return; } \
		SIMFILE->name_length = 0; \
		for (int i = 0; i < MAX_FILENAME_SIZE; i++) { SIMFILE->name[i] = '\0'; } \
	} while (0)

#define SIMFILE_OPEN(HANDLE, ARG, NAME, ACCESS, SIMULATOR) \
    do { \
		checkCLIfile(ARG, NAME, SIMULATOR); \
		if (SIMULATOR->status != NO_ERROR) { return; } \
		strcpy(HANDLE->name,  ARG); \
		HANDLE->name_length = strlen(HANDLE->name); \
		HANDLE->handle = fopen(HANDLE->name, ACCESS); \
	} while (0)

#define CLOSE_FILE(HANDLE) do { if (NULL != HANDLE) { fclose(HANDLE); HANDLE = NULL; } } while (0)

/*===================================
|          ERROR CODES              |
====================================*/
typedef enum {
	NO_ERROR = 0,
	INCORRECT_CLI_ARGUMENTS,
	INPUT_FILE_DOES_NOT_EXISTS,
	FILE_BAD_NAME,
	FILE_BAD_EXTENSION,
	MEMORY_ALLOCATION_ERROR,
	FILE_CLOSED,
	HALT_SIMULATOR,
	NUM_OF_ERRORS
} ErrorCode;

/*===================================
|            STRUCTS                |
====================================*/
typedef struct {
	char  name[MAX_FILENAME_SIZE];
	int   name_length;
	FILE* handle;
} SimFile;

typedef struct {
	SimFile* memin;
	SimFile* diskin;
	SimFile* irq2in;
	SimFile* memout;
	SimFile* regout;
	SimFile* trace;
	SimFile* hwregtrace;
	SimFile* cycles;
	SimFile* leds;
	SimFile* display7seg;
	SimFile* diskout;
	SimFile* monitor;
} SimulatorFiles;

/*===================================
|           TYPEDEFS                |
====================================*/
typedef char unsigned bool;

#endif // __GLOBAL_H__