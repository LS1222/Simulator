#ifndef __MEMORY_H__
#define __MEMORY_H__

/*===================================
|           INCLUDES                |
====================================*/
#include <stdlib.h>

/*===================================
|           DEFINES                 |
====================================*/
#define MEMORY_SIZE 4096
#define REGISTER_DEFAULT 0
#define MEMORY_WORD_BTIS 20
#define MAX_MEM_LINE_LENGTH 5
#define HD_SECTOR_SIZE      128
#define HD_NUM_OF_SECTORS   128

/*===================================
|           TYPEDEFS                |
====================================*/
typedef int unsigned Register;
typedef int unsigned IORegister;
typedef int          SignedRegister;

/*===================================
|            ENUMS                  |
====================================*/
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

typedef enum {
	IO_REGISTER_IRQ0_ENABLE,
	IO_REGISTER_IRQ1_ENABLE,
	IO_REGISTER_IRQ2_ENABLE,
	IO_REGISTER_IRQ0_STATUS,
	IO_REGISTER_IRQ1_STATUS,
	IO_REGISTER_IRQ2_STATUS,
	IO_REGISTER_IRQ_HANDLER,
	IO_REGISTER_IRQ_RETURN,
	IO_REGISTER_CLKS,
	IO_REGISTER_LEDS,
	IO_REGISTER_DISPLAY_7SEG,
	IO_REGISTER_TIMER_ENABLE,
	IO_REGISTER_TIMER_CURRENT,
	IO_REGISTER_TIMER_MAX,
	IO_REGISTER_DISK_CMD,
	IO_REGISTER_DISK_SECTOR,
	IO_REGISTER_DISK_BUFFER,
	IO_REGISTER_DISK_STATUS,
	IO_REGISTER_RESERVED0,
	IO_REGISTER_RESERVED1,
	IO_REGISTER_RESERVED2,
	IO_REGISTER_MONITOR_ADDR,
	IO_REGISTER_MONITOR_DATA,
	IO_REGISTER_MONITOR_CMD,
	NUM_OF_IO_REGISTERS
} IORegisterOpcode;

typedef struct {
	int unsigned word : MEMORY_WORD_BTIS;
} MemoryWord;

// Memories
typedef MemoryWord* SimulatorMemory;
typedef MemoryWord  HDSector[HD_SECTOR_SIZE];
typedef HDSector    HardDisk[HD_NUM_OF_SECTORS];
typedef HardDisk*   SimulatorHardDisk;

static const char* IORegisterName[NUM_OF_IO_REGISTERS] = {
	"irq0enable",
	"irq1enable",
	"irq2enable",
	"irq0status",
	"irq1status",
	"irq2status",
	"irqhandler",
	"irqreturn",
	"clk",
	"leds",
	"display7seg",
	"timerenable",
	"timercurrent",
	"timermax",
	"diskcmd",
	"disksector",
	"diskbuffer",
	"diskstatus",
	"reserved0",
	"reserved1",
	"reserved2",
	"monitoraddr",
	"monitordata",
	"monitorcmd"
};

#endif // __MEMORY_H__