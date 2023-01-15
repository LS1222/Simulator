#include "main.h"

void InitializeSimulator(Simulator* sim) {
	sim->status = NO_ERROR;
	sim->cycles = 0;
	sim->regs[REGISTER_PC] = 0;

	// Allocate all files handles.
	SIMFILE_INIT(sim->files.memin,  sim)
	SIMFILE_INIT(sim->files.memout, sim)
	SIMFILE_INIT(sim->files.regout, sim)
	SIMFILE_INIT(sim->files.trace,  sim)
	SIMFILE_INIT(sim->files.cycles, sim)

	// Allocate all the registers of the simulator.
	for (int i = 0; i < NUM_OF_REGISTERS; i++) {
		sim->regs[i] = (Register*)malloc(sizeof(Register));
		if (NULL == sim->regs[i]) {
			sim->status = MEMORY_ALLOCATION_ERROR;
			return;
		}
	}

	// Allocate memory.
	sim->mem = (SimulatorMemory)calloc(MEMORY_SIZE, sizeof(MemoryWord));
	if (NULL == sim->mem) {
		sim->status = MEMORY_ALLOCATION_ERROR;
		return;
	}

}

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

void checkCLIfile(char* act_file, const char* exp_file, Simulator* sim) {
	char* act_name = (char*)malloc(MAX_FILENAME_SIZE);
	char* exp_name = (char*)malloc(MAX_FILENAME_SIZE);
	char* act_ext = (char*)malloc(MAX_FILENAME_SIZE);
	char* exp_ext = (char*)malloc(MAX_FILENAME_SIZE);

	splitFileExtention(act_file, act_name, act_ext);
	splitFileExtention(exp_file, exp_name, exp_ext);

	// Check file name.
	if (strcmp(act_name, exp_name)) {
		printf("Incorrect filename. Expected %s but got %s\n", exp_name, act_name);
		sim->status = FILE_BAD_NAME;
		return;
	}

	// Check file extension.
	if (strcmp(act_ext, exp_ext)) {
		printf("Bad extension. Expected %s.%s but got %s.%s\n", exp_name, exp_ext, act_name, act_ext);
		sim->status = FILE_BAD_EXTENSION;
		return;
	}
}

void ParseCLI(int argc, char* argv[], Simulator* sim) {

	if (argc != 6) {
		printf("Incorrect number of arguments\n");

		// Return an error code.
		sim->status = INCORRECT_CLI_ARGUMENTS;
	}

	// Open the files.
	SIMFILE_OPEN(sim->files.memin,  argv[1], RAM_INPUT_FILE,       READ,  sim)
	SIMFILE_OPEN(sim->files.memout, argv[2], RAM_OUTPUT_FILE,      WRITE, sim)
	SIMFILE_OPEN(sim->files.regout, argv[3], REGISTER_OUTPUT_FILE, WRITE, sim)
	SIMFILE_OPEN(sim->files.trace,  argv[4], TRACE_OUTPUT_FILE,    WRITE, sim)
	SIMFILE_OPEN(sim->files.cycles, argv[5], CYCLE_OUTPUT_FILE,    WRITE, sim)
}

void InitializeMemories(Simulator* sim) {
	char line[MAX_MEM_LINE_LENGTH + 1];
	int  address = 0;

	// Initialize all the registers of the simulator.
	for (int i = 0; i < NUM_OF_REGISTERS; i++) {
		sim->regs[i] = 0;
	}

	// Initialize memory from file.
	while (!feof(sim->files.memin->handle)) {

		// Read the memory line.
		fgets(line, MAX_MEM_LINE_LENGTH + 1, sim->files.memin->handle);

		// Read the \n.
		fgetc(sim->files.memin->handle);

		// Covert to number.
		sscanf(line, "%d", sim->mem[address++].word);
		// sim->mem[address++].word = atoi(line);
		// address++;
	}
}

void PrintMemory(Simulator* sim) {
	char line[MAX_MEM_LINE_LENGTH + 1];

	// Check if the file is closed.
	if (feof(sim->files.memout->handle)) {
		sim->status = FILE_CLOSED;
		return;
	}

	// Write all the memory to the output file.
	for (int address = 0; address < MEMORY_SIZE; address++) {
		// Convert the memory word to a string line.
		sprintf_s(line, MAX_MEM_LINE_LENGTH + 1, "%" STR(MAX_MEM_LINE_LENGTH) "X\n", sim->mem[address].word);

		// Write to file.
		fputs(line, sim->files.memout->handle);
	}
}

void PrintRegisters(Simulator* sim) {
	// Check if the file is closed.
	if (feof(sim->files.regout->handle)) {
		sim->status = FILE_CLOSED;
		return;
	}

	// Print all the registers without registers 0 and 1 (zero and imm).
	for (RegisterOpcode i = REGISTER_RESULT_VALUE; i <= REGISTER_RETURN_ADDRESS; i++) {
		fprintf_s(sim->files.regout->handle, "%8X\n", sim->regs[i]);
	}
}

void FinalizeSimulation(Simulator* sim) {
	// Close all the files.
	CLOSE_FILE(sim->files.memin->handle, sim)
	CLOSE_FILE(sim->files.memout->handle, sim)
	CLOSE_FILE(sim->files.regout->handle, sim)
	CLOSE_FILE(sim->files.trace->handle, sim)
	CLOSE_FILE(sim->files.cycles->handle, sim)

	// Free the simulation handles.
	free(sim->files.memin);
	free(sim->files.memout);
	free(sim->files.regout);
	free(sim->files.trace);
	free(sim->files.cycles);

	// Free the memory.
	free(sim->mem);
	for (int i = 0; i < NUM_OF_REGISTERS; i++) { free(sim->regs[i]); }
}

int main(int argc, char* argv[]) {
	Simulator sim;

	// Initialize simulator.
	InitializeSimulator(&sim);

	// Check the command line arguments.
	ParseCLI(argc, argv, &sim);

	InitializeMemories(&sim);

	// General idea:
	// Run the main loop of the CPU (simulated) with the inputs from the compiler.
	if (NO_ERROR == sim.status) {
		mainLoop(&sim);

		// Outputs.
		PrintMemory(&sim);
		PrintRegisters(&sim);
	}

	FinalizeSimulation(&sim);

	return (sim.status);
}