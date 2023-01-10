#ifndef __LOOP_C__
#define __LOOP_C__

#include "Loop.h"

ErrorCode mainLoop(GlobalRegisters* regs, SimulatorFiles* files) {
	ErrorCode status = NO_ERROR;
	char      line[MAX_MEM_LINE_LENGTH + 1];

	while (HALT != status) {
		status |= Fetch(files, &line);
		status |= Decode(regs, files, &line);
		status |= Execute(regs, files);
	}

	return (status);
}

ErrorCode Fetch(SimulatorFiles* files, char* line) {
	// Handle EOF.
	// TODO: What to do when the simulator gets to the EOF.
	if (feof(files->memin->handle)) {
		return (MEM_EOF);
	}

	// Get a line from the memin.txt file.
	fgets(line, MAX_MEM_LINE_LENGTH + 1, files->memin->handle);

	return (NO_ERROR);
}

ErrorCode Decode(GlobalRegisters* regs, SimulatorFiles* files) {
	// Parse the command into I opcode or R opcode.

	// Advance the PC register.
	// R format by 1, I format by 2.

	return (NO_ERROR);
}

ErrorCode Execute(GlobalRegisters* regs, SimulatorFiles* files) {
	char* instruction = NULL;
	// Perform the operation.

	// Write to trace.txt.
	fprintf(files->trace->handle, "%2X ", regs->PC);
	fprintf(files->trace->handle, "%s ", instruction);
	fprintf(files->trace->handle, "00000000 ");
	// TODO: Add immidiate register print.
	fprintf(files->trace->handle, "%8X ",  regs->v0);
	fprintf(files->trace->handle, "%8X ",  regs->arg_regs.a0);
	fprintf(files->trace->handle, "%8X ",  regs->arg_regs.a1);
	fprintf(files->trace->handle, "%8X ",  regs->arg_regs.a2);
	fprintf(files->trace->handle, "%8X ",  regs->arg_regs.a3);
	fprintf(files->trace->handle, "%8X ",  regs->tmp_regs.t0);
	fprintf(files->trace->handle, "%8X ",  regs->tmp_regs.t1);
	fprintf(files->trace->handle, "%8X ",  regs->tmp_regs.t2);
	fprintf(files->trace->handle, "%8X ",  regs->saved_regs.s0);
	fprintf(files->trace->handle, "%8X ",  regs->saved_regs.s1);
	fprintf(files->trace->handle, "%8X ",  regs->saved_regs.s2);
	fprintf(files->trace->handle, "%8X ",  regs->ptr_regs.gp);
	fprintf(files->trace->handle, "%8X ",  regs->ptr_regs.sp);
	fprintf(files->trace->handle, "%8X\n", regs->ptr_regs.ra);

	return (NO_ERROR);
}

#endif // __LOOP_C__