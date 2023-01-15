#ifndef __ISA_C__
#define __ISA_C__

#include "ISA.h"

void add(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	*rd = *rs + *rt;
}

void sub(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	*rd = *rs - *rt;
}

void mul(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	// TODO: Make sure the multiplication is correct (for signed values).
	*rd = *rs * *rt;
}

void and(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	*rd = *rs & *rt;
}

void or(Simulator * sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	*rd = *rs | *rt;
}

void xor(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	*rd = *rs ^ *rt;
}

void sll(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	// TODO: Verify that 0s are being inserted in the right.
	*rd = *rs << *rt;
}

void sra(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	// TODO: Verify that the shift is arithmetic.
	*rd = *rs >> *rt;
}

void srl(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	// TODO: Make sure the MSBs are 0s.
	*rd = *rs >> *rt;
}

void beq(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	if (*rs == *rt) {
		sim->regs[REGISTER_PC] = *rd;
	}
}

void bne(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	if (*rs != *rt) {
		sim->regs[REGISTER_PC] = *rd;
	}
}

void blt(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	if (*rs < *rt) {
		sim->regs[REGISTER_PC] = *rd;
	}
}

void bgt(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	if (*rs > *rt) {
		sim->regs[REGISTER_PC] = *rd;
	}
}

void ble(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	if (*rs <= *rt) {
		sim->regs[REGISTER_PC] = *rd;
	}
}

void bge(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Operation.
	if (*rs >= *rt) {
		sim->regs[REGISTER_PC] = *rd;
	}
}

void jal(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];

	sim->regs[REGISTER_PC] = sim->regs[sim->command.rs];
	// TODO: command->rd = Next address?
}

void lw(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Load from memory the information.
	*rd = sim->mem[*rs + *rt].word;
	sim->cycles++;
}

void sw(Simulator* sim) {
	Register* rd = sim->regs[sim->command.rd];
	Register* rs = sim->regs[sim->command.rs];
	Register* rt = sim->regs[sim->command.rt];

	// Save to memory the information.
	sim->mem[*rs + *rt].word = *rd;
	sim->cycles++;
}

#endif // __ISA_C__