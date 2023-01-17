#ifndef __LOOP_H__
#define __LOOP_H__

/*===================================
|           INCLUDES                |
====================================*/
#include "Global.h"
#include "Simulator.h"
#include "ISA.h"

/*===================================
|           DEFINES                 |
====================================*/
#define RT_MASK     0x0000F
#define RS_MASK     0x000F0
#define RD_MASK     0x00F00
#define OPCODE_MASK 0xFF000

/*===================================
|        FUNCTIONS PROTOTYPE        |
====================================*/
void mainLoop(Simulator* sim);
void Fetch   (Simulator* sim);
void Decode  (Simulator* sim);
void Execute (Simulator* sim);

#endif // __LOOP_H__