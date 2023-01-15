#ifndef __INSTRUCTION_FORMATS_H__
#define __INSTRUCTION_FORMATS_H__

typedef enum {
	RFORMAT,
	IFORMAT,
	NUM_OF_OPCODE_TYPES
} OpcodeType;

typedef struct {
	int unsigned rt     : 4;
	int unsigned rs     : 4;
	int unsigned rd     : 4;
	int unsigned opcode : 8;
	int unsigned imm    : 20;
} CommandFormat;

#endif // __INSTRUCTION_FORMATS_H__