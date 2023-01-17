#ifndef __ISA_C__
#define __ISA_C__

/*===================================
|           INCLUDES                |
====================================*/
#include "ISA.h"

/*===================================
|           FUNCTIONS               |
====================================*/
void add(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) + (*rt);
}

void sub(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) - (*rt);
}

void mul(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) * (*rt);
}

void and(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) & (*rt);
}

void or(Simulator * sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) | (*rt);
}

void xor(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) ^ (*rt);
}

void sll(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) << (*rt);
}

void sra(Simulator* sim) {
	
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Convert to a signed register.
	SignedRegister* rss = rs;

	// Operation.
	(*rd) = (*rss) >> (*rt);
}

void srl(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	(*rd) = (*rs) >> (*rt);
}

void beq(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	if ((*rs) == (*rt)) {
		sim->regs[REGISTER_PC] = (*rd);
	}
}

void bne(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	if ((*rs) != (*rt)) {
		sim->regs[REGISTER_PC] = (*rd);
	}
}

void blt(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	if ((*rs) < (*rt)) {
		sim->regs[REGISTER_PC] = (*rd);
	}
}

void bgt(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	if ((*rs) > (*rt)) {
		sim->regs[REGISTER_PC] = (*rd);
	}
}

void ble(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	if ((*rs) <= (*rt)) {
		sim->regs[REGISTER_PC] = (*rd);
	}
}

void bge(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Operation.
	if ((*rs) >= (*rt)) {
		sim->regs[REGISTER_PC] = (*rd);
	}
}

void jal(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);

	// Save the next instruction in RD.
	(*rd) = sim->regs[REGISTER_PC] + 1;

	// Instruction is IFormat, increase by + 2.
	if (REGISTER_IMMIDIATE == sim->command.rs) {
		(*rd) = sim->regs[REGISTER_PC] + 2;
	}

	// Jump to RS label / register.
	sim->regs[REGISTER_PC] = (*rs);
}

void lw(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Load from memory the information.
	(*rd) = sim->mem[(*rs) + (*rt)].word;

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
}

void sw(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Save to memory the information.
	sim->mem[(*rs) + (*rt)].word = (*rd);

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
}

void reti(Simulator* sim) {
	sim->regs[REGISTER_PC] = sim->io_regs[IO_REGISTER_IRQ_RETURN];
	sim->isr_mode = 0;
}

void in(Simulator* sim) {
	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Input Operation.
	if (IO_REGISTER_MONITOR_CMD != (*rs) + (*rt)) {
		(*rd) = sim->io_regs[(*rs) + (*rt)];

	// Reading the Monitor CMD register yields 0.
	} else {
		(*rd) = 0;
	}

	// Print HW Trace.
	fprintf(sim->files.hwregtrace->handle, "%0d READ %s %08X\n", sim->cycles, IORegisterName[(*rs) + (*rt)], (*rd));
}

void out(Simulator* sim) {
	int unsigned row = 0;
	int unsigned col = 0;

	REGS_IMM_ASSIGN(rd);
	REGS_IMM_ASSIGN(rs);
	REGS_IMM_ASSIGN(rt);

	// Output Operation.
	if (IO_REGISTER_MONITOR_CMD != (*rs) + (*rt)) {
		sim->io_regs[(*rs) + (*rt)] = (*rd);
	} else {
		row = sim->io_regs[IO_REGISTER_MONITOR_ADDR / MONITOR_WIDTH];
		col = sim->io_regs[IO_REGISTER_MONITOR_ADDR % MONITOR_WIDTH];
		(*sim->monitor)[row][col] = sim->io_regs[IO_REGISTER_MONITOR_DATA];
	}

	// Print HW Trace.
	fprintf(sim->files.hwregtrace->handle, "%0d WRITE %s %08X\n", sim->cycles, IORegisterName[(*rs) + (*rt)], (*rd));

	// Print the LED status.
	if (IO_REGISTER_LEDS == (*rs) + (*rt)) {
		fprintf(sim->files.leds->handle, "%0d %08X\n", sim->cycles, sim->io_regs[IO_REGISTER_LEDS]);
	}

	// Print the LED status.
	if (IO_REGISTER_DISPLAY_7SEG == (*rs) + (*rt)) {
		fprintf(sim->files.display7seg->handle, "%0d %08X\n", sim->cycles, sim->io_regs[IO_REGISTER_DISPLAY_7SEG]);
	}
}

void halt(Simulator* sim) {
	sim->status = HALT_SIMULATOR;
}

#endif // __ISA_C__