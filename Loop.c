#ifndef __LOOP_C__
#define __LOOP_C__

#include "Loop.h"

void mainLoop(Simulator* sim) {
	while (HALT_SIMULATOR != sim->status) {
		Fetch(sim);
		Decode(sim);
		Execute(sim);
	}
}

void Fetch(Simulator* sim) {
	sim->lines[0] = sim->mem[sim->regs[REGISTER_PC]];
	sim->lines[1] = sim->mem[(sim->regs[REGISTER_PC] + 1) % MEMORY_SIZE];
}

void Decode(Simulator* sim) {
	
	// Parse the command into I command or R command.
	// The default is R Command.
	sim->command_type = RFORMAT;
	sim->command.opcode = (sim->lines[0].word & OPCODE_MASK) >> 12;
	sim->command.rd = (sim->lines[0].word & RD_MASK) >> 8;
	sim->command.rs = (sim->lines[0].word & RS_MASK) >> 4;
	sim->command.rt = sim->lines[0].word & RT_MASK;

	// Advance the PC register.
	// R command by 1, I command by 2.
	sim->regs[REGISTER_PC]++;

	// Check for immidiate format in the registers' nums.
	if ((REGISTER_IMMIDIATE == sim->command.rd) ||
		(REGISTER_IMMIDIATE == sim->command.rs) ||
		(REGISTER_IMMIDIATE == sim->command.rt)) {

		// IFormat command.
		sim->command_type = IFORMAT;
		sim->command.imm = sim->lines[1].word;
		sim->regs[REGISTER_PC]++;

		// Advance the clock (load the immidiate register).
		sim->regs[REGISTER_IMMIDIATE] = sim->lines[1].word;
		sim->cycles++;
	}
}

void Execute(Simulator* sim) {
	// Convert the command by format type.
	if ((RFORMAT != sim->command_type) && (IFORMAT != sim->command_type)) {
		sim->status = BAD_COMMAND_FORMAT;
		return;
	}

	// Advance the clock.
	sim->cycles++;

	// Perform the operation.
	opcode_functions[sim->command.opcode](sim);
	

	// Write to trace.txt.
	fprintf(sim->files.trace->handle, "%3X ", sim->regs[REGISTER_PC]);
	fprintf(sim->files.trace->handle, "%8X ", sim->lines[0].word);
	for (RegisterOpcode i = REGISTER_ZERO; i <= REGISTER_STACK_POINTER; i++) {
		fprintf(sim->files.trace->handle, "%8X ", sim->regs[i]);
	}
	fprintf(sim->files.trace->handle, "%8X\n", sim->regs[REGISTER_RETURN_ADDRESS]);
}

#endif // __LOOP_C__