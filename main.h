#ifndef __MAIN_H__
#define __MAIN_H__

// Defines.
#define _CRT_SECURE_NO_WARNINGS

// Include libraries.
#include <stdio.h>
#include "GlobalDefines.h"
#include "Loop.h"
#include "Simulator.h"

// Funciton prototypes.
void InitializeSimulator(Simulator* sim);
void splitFileExtention(char* file_name, char* name, char* ext);
void checkCLIfile(char* act_name, const char* exp_name, Simulator* sim);
void ParseCLI(int argc, char* argv[], Simulator* sim);
void InitializeMemories(Simulator* sim);
void PrintMemory(Simulator* sim);
void PrintRegisters(Simulator* sim);
void FinalizeSimulation(Simulator* sim);

#endif // __MAIN_H__
