#ifndef __MAIN_H__
#define __MAIN_H__

/*===================================
|           DEFINES                 |
====================================*/
#define _CRT_SECURE_NO_WARNINGS

/*===================================
|           INCLUDES                |
====================================*/
#include <stdio.h>
#include "Global.h"
#include "Simulator.h"
#include "Monitor.h"
#include "Loop.h"

/*===================================
|        FUNCTIONS PROTOTYPE        |
====================================*/
void InitializeSimulator(Simulator* sim);
void splitFileExtention (char* file_name, char* name, char* ext);
void checkCLIfile       (char* act_name, const char* exp_name, Simulator* sim);
void ParseCLI           (int argc, char* argv[], Simulator* sim);
void InitializeMemories (Simulator* sim);
void PrintMemory        (Simulator* sim);
void PrintRegisters     (Simulator* sim);
void PrintCycles        (Simulator* sim);
void PrintHardDisk      (Simulator* sim);
void PrintMonitor       (Simulator* sim);
void FinalizeSimulation (Simulator* sim);

#endif // __MAIN_H__