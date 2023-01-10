#include "main.h"

void splitFileExtention(char* file_name, char* name, char* ext) {
	int   sub_index = 0;
	char* substring = NULL;

	// Check pointers.
	if (NULL == file_name || NULL == name || NULL == ext) {
		return;
	}

	substring = name;
	for (int i = 0; i < strlen(file_name); i++) {

		// When finding a '.' delimiter, start collecting the extension.
		if (file_name[i] == '.') {
			substring[sub_index] = '\0';
			sub_index = 0;
			substring = ext;
			continue;

			// TODO: Corner case - file contains multiple delimiters.
		}

		// Get the character into the substring [filename/extension].
		substring[sub_index++] = file_name[i];
	}
	
	// Add the NULL terminator to the string.
	substring[sub_index] = '\0';
}

ErrorCode checkCLIfile(char* act_file, const char* exp_file) {
	char* act_name = (char*)malloc(MAX_FILENAME_SIZE);
	char* exp_name = (char*)malloc(MAX_FILENAME_SIZE);
	char* act_ext  = (char*)malloc(MAX_FILENAME_SIZE);
	char* exp_ext  = (char*)malloc(MAX_FILENAME_SIZE);

	splitFileExtention(act_file, act_name, act_ext);
	splitFileExtention(exp_file, exp_name, exp_ext);

	// Check file name.
	if (strcmp(act_name, exp_name)) {
		printf("Incorrect filename. Expected %s but got %s\n", exp_name, act_name);
		return (FILE_BAD_NAME);
	}

	// Check file extension.
	if (strcmp(act_ext, exp_ext)) {
		printf("Bad extension. Expected %s.%s but got %s.%s\n", exp_name, exp_ext, act_name, act_ext);
		return (FILE_BAD_EXTENSION);
	}

	return (NO_ERROR);
}

ErrorCode ParseCLI(int argc, char* argv[], SimulatorFiles* files) {
	ErrorCode status = NO_ERROR;

	if (argc != 6) {
		printf("Incorrect number of arguments\n");

		// Return an error code.
		return (INCORRECT_CLI_ARGUMENTS);
	}

	// Open the files.
	SIMFILE_OPEN(files->memin,  argv[1], "memin.txt",  READ)
	SIMFILE_OPEN(files->memout, argv[2], "memout.txt", WRITE)
	SIMFILE_OPEN(files->regout, argv[3], "regout.txt", WRITE)
	SIMFILE_OPEN(files->trace,  argv[4], "trace.txt",  WRITE)
	SIMFILE_OPEN(files->cycles, argv[5], "cycles.txt", WRITE)

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
	SimulatorFiles files;
	GlobalRegisters regs;

	// Check the command line arguments.
	status = ParseCLI(argc, argv, &files);

	// Initialize all the registers of the simulator.
	InitializeRegisters(&regs);

	// General idea:
	// Run the main loop of the CPU (simulated) with the inputs from the compiler.
	if (!status) {
		status = mainLoop(&regs, &files);
	}

	// TODO: Report status.

	return (status);
}