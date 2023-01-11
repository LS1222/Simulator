#include "main.h"

ErrorCode checkCLIfile(char* act_name, const char* exp_name, const char* exp_extention) {
	int   sub_index = 0;
	char* extension = NULL;
	char* filename  = NULL;
	char* substring = NULL;

	filename = (char*)malloc(strlen(act_name));
	extension = (char*)malloc(strlen(act_name));
	substring = filename;
	for (int i = 0; i < strlen(act_name); i++) {

		// When finding a '.' delimiter, start collecting the extension.
		if (act_name[i] == '.') {
			sub_index = 0;
			substring = extension;

			// TODO: Corner case - file contains multiple delimiters.
		}

		// Get the character into the substring [filename/extension].
		substring[sub_index++] = act_name[i];
	}

	// Check file name.
	if (strcmp(filename, exp_name)) {
		printf("Incorrect filename. Expected %s.%s but got %s\n", exp_name, exp_extention, act_name);
		return (FILE_BAD_NAME);
	}

	// Check file extension.
	if (strcmp(extension, exp_extention)) {
		printf("Bad extension. Expected %s.%s but got %s\n", exp_name, exp_extention, act_name);
		return (FILE_BAD_EXTENSION);
	}

	return (NO_ERROR);
}

ErrorCode ParseCLI(int argc, char* argv[], SimulatorFiles* file_names) {
	ErrorCode status = NO_ERROR;

	if (argc != 5) {
		printf("Incorrect number of arguments\n");

		// Return an error code.
		return (INCORRECT_CLI_ARGUMENTS);
	}

	// Get the names from command line.
	file_names->memin  = argv[0];
	file_names->memout = argv[1];
	file_names->regout = argv[2];
	file_names->trace  = argv[3];
	file_names->cycles = argv[4];

	// Check the files.
	CHECK_FILE_RETURN_STATUS(file_names->memin,  "memin",  "txt");
	CHECK_FILE_RETURN_STATUS(file_names->memout, "memout", "txt");
	CHECK_FILE_RETURN_STATUS(file_names->regout, "regout", "txt");
	CHECK_FILE_RETURN_STATUS(file_names->trace,  "trace",  "txt");
	CHECK_FILE_RETURN_STATUS(file_names->cycles, "cycles", "txt");

	// Command line arguments are ok and parsed.
	return (status);
}

void InitializeRegisters(GlobalRegisters* regs) {
	// Global Registers.
	regs->v0 = 0;

	// Argument Registers.
	regs->arg_regs.a0 = 0;
	regs->arg_regs.a1 = 0;
	regs->arg_regs.a2 = 0;
	regs->arg_regs.a3 = 0;

	// Temporary Registers.
	regs->tmp_regs.t0 = 0;
	regs->tmp_regs.t1 = 0;
	regs->tmp_regs.t2 = 0;

	// Saved Registers.
	regs->saved_regs.s0 = 0;
	regs->saved_regs.s1 = 0;
	regs->saved_regs.s2 = 0;

	// Pointer Registers.
	regs->ptr_regs.gp = 0;
	regs->ptr_regs.sp = 0;
	regs->ptr_regs.ra = 0;

	// IO Registers.
	// TODO: Bonus.
}

int main(int argc, char* argv[]) {
	ErrorCode status = NO_ERROR;
	SimulatorFiles file_names;
	GlobalRegisters regs;

	// Check the command line arguments.
	status = ParseCLI(argc, argv, &file_names);

	// Initialize all the registers of the simulator.
	InitializeRegisters(&regs);

	// General idea:
	// Run the main loop of the CPU (simulated) with the inputs from the compiler.
	if (!status) {

	}

	return (status);
}