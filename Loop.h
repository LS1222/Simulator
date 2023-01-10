#ifndef __LOOP_H__
#define __LOOP_H__

// Include libraries.
#include "GlobalDefines.h"
#include "Registers.h"

// Funciton prototypes.
ErrorCode mainLoop(GlobalRegisters* regs, SimulatorFiles* files);
ErrorCode Fetch(SimulatorFiles* files, char* line);
ErrorCode Decode(GlobalRegisters* regs, SimulatorFiles* files);
ErrorCode Execute(GlobalRegisters* regs, SimulatorFiles* files);

#endif // __LOOP_H__