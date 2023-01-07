#ifndef __LOOP_C__
#define __LOOP_C__

#include "Loop.h"

void mainLoop() {
	int halted = 0;

	while (!halted) {
		Fetch();
		Decode();
		Execute();
	}
}

void Fetch() {
	// Get the next command from the memory file.
}

void Decode() {
	// Parse the command into I opcode or R opcode.

	// Advance the PC register.
	// R format by 1, I format by 2.
}

void Execute() {
	// Perform the operation.
}

#endif // __LOOP_C__