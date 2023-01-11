#ifndef __GLOBAL_DEFINES_H__
#define __GLOBAL_DEFINES_H__

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
#define CLOCK_OUTPUT_FILE "cycles.txt"
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
	NUM_OF_ERRORS
} ErrorCode;

#endif // __GLOBAL_DEFINES_H__