#ifndef __INSTRUCTION_FORMATS_H__
#define __INSTRUCTION_FORMATS_H__

typedef struct RFormat {
	int unsigned rt     : 4;
	int unsigned rs     : 4;
	int unsigned Rd     : 4;
	int unsigned opcode : 8;
} RFormat;

typedef struct IFormat {
	int unsigned rt     : 4;
	int unsigned rs     : 4;
	int unsigned rd     : 4;
	int unsigned opcode : 8;
	int unsigned imm    : 20;
} IFormat;

#endif // __INSTRUCTION_FORMATS_H__