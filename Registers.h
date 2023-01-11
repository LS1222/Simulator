#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#define REGISTER_DEFAULT 0;
typedef int unsigned Register;

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
	Register a0 : 32;
	Register a1 : 32;
	Register a2 : 32;
	Register a3 : 32;
} ArgumentRegisters;

typedef struct {
	Register t0 : 32;
	Register t1 : 32;
	Register t2 : 32;
} TempRegisters;

typedef struct {
	Register s0 : 32;
	Register s1 : 32;
	Register s2 : 32;
}SavedRegisters;

typedef struct {
	Register gp : 32; // Global Pointer (static data).
	Register sp : 32; // Stack Pointer.
	Register ra : 32; // Return Address.
} PointerRegisters;

typedef struct {
	Register zero : 32; // Constant to 0.
	Register imm  : 32; // ?????
	Register v0   : 32; // Result Value.
	ArgumentRegisters  arg_regs;
	TempRegisters      tmp_regs;
	SavedRegisters     saved_regs;
	PointerRegisters   ptr_regs;
	// IORegisters        io_regs; // Bonus.
} GlobalRegisters;

#endif // _REGISTERS_H__
