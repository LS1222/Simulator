#ifndef __LOOP_C__
#define __LOOP_C__

/*===================================
|           INCLUDES                |
====================================*/
#include "Loop.h"

/*===================================
|           FUNCTIONS               |
====================================*/
void mainLoop(Simulator* sim) {
	while (NO_ERROR == sim->status) {
		Fetch(sim);
		Decode(sim);
	
		// IRQ handling in normal operation.
		// Go to an ISR (Interrupt Service Routine).
		if (!sim->isr_mode) {

			// Get the irq status.
			sim->irq0 = sim->io_regs[IO_REGISTER_IRQ0_ENABLE] & sim->io_regs[IO_REGISTER_IRQ0_STATUS];
			sim->irq1 = sim->io_regs[IO_REGISTER_IRQ1_ENABLE] & sim->io_regs[IO_REGISTER_IRQ1_STATUS];
			sim->irq2 = sim->io_regs[IO_REGISTER_IRQ2_ENABLE] & sim->io_regs[IO_REGISTER_IRQ2_STATUS];

			// Store previous PC value (return address).
			sim->io_regs[IO_REGISTER_IRQ_RETURN] = sim->regs[REGISTER_PC];

			// The service routine is stored at the IRQ HANDLE io register.
			sim->regs[REGISTER_PC] = sim->io_regs[IO_REGISTER_IRQ_HANDLER];

			// Reset the interrupts (they have been read already).
			sim->io_regs[IO_REGISTER_IRQ0_STATUS] = REGISTER_DEFAULT;
			sim->io_regs[IO_REGISTER_IRQ1_STATUS] = REGISTER_DEFAULT;
			sim->io_regs[IO_REGISTER_IRQ2_STATUS] = REGISTER_DEFAULT;

		// Perform the opcode.
		} else {	
			Execute(sim);
		}
	}
}

void Fetch(Simulator* sim) {
	sim->lines[0] = sim->mem[sim->regs[REGISTER_PC]];
	sim->lines[1] = sim->mem[(sim->regs[REGISTER_PC] + 1) % MEMORY_SIZE];
}

void Decode(Simulator* sim) {
	
	// Parse the command into I command or R command.
	// The default is R Command.
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
		sim->command.imm = sim->lines[1].word;
		sim->regs[REGISTER_PC]++;

		// Advance the clock (load the immidiate register).
		sim->regs[REGISTER_IMMIDIATE] = sim->lines[1].word;
		sim->cycles++;

		// Advance the timer.
		if (sim->io_regs[IO_REGISTER_TIMER_ENABLE]) {
			sim->io_regs[IO_REGISTER_TIMER_CURRENT]++;

			if (sim->io_regs[IO_REGISTER_TIMER_CURRENT] == sim->io_regs[IO_REGISTER_TIMER_MAX]) {
				// Reset the value of the timer.
				sim->io_regs[IO_REGISTER_TIMER_CURRENT] = REGISTER_DEFAULT;

				// Set the interrupts.
				sim->io_regs[IO_REGISTER_IRQ0_STATUS] = 1;
			}
		}
	}
}

void Execute(Simulator* sim) {
	// Advance the clock.
	sim->cycles++;

	// Advance the timer.
	if (sim->io_regs[IO_REGISTER_TIMER_ENABLE]) {
		sim->io_regs[IO_REGISTER_TIMER_CURRENT]++;

		if (sim->io_regs[IO_REGISTER_TIMER_CURRENT] == sim->io_regs[IO_REGISTER_TIMER_MAX]) {
			// Reset the value of the timer.
			sim->io_regs[IO_REGISTER_TIMER_CURRENT] = REGISTER_DEFAULT;

			// Set the interrupts.
			sim->io_regs[IO_REGISTER_IRQ0_STATUS] = 1;
		}
	}

	// Perform the operation.
	opcode_functions[sim->command.opcode](sim);
	
	// Print Trace.
	fprintf(sim->files.trace->handle, "%03X ", sim->regs[REGISTER_PC]);
	fprintf(sim->files.trace->handle, "%08X ", sim->lines[0].word);
	for (RegisterOpcode i = REGISTER_ZERO; i <= REGISTER_STACK_POINTER; i++) {
		fprintf(sim->files.trace->handle, "%08X ", sim->regs[i]);
	}

	fprintf(sim->files.trace->handle, "%08X", sim->regs[REGISTER_RETURN_ADDRESS]);
	fflush(sim->files.trace->handle);
	if (OPCODE_HALT != sim->command.opcode) {
		fprintf(sim->files.trace->handle, "\n");
	}
}

#endif // __LOOP_C__