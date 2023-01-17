/*===================================
|           INCLUDES                |
====================================*/
#include "main.h"

/*===================================
|           FUNCTIONS               |
====================================*/
void InitializeSimulator(Simulator* sim) {
	sim->status = NO_ERROR;
	sim->cycles = 0;
	sim->regs[REGISTER_PC] = 0;

	// Allocate all files handles.
	SIMFILE_INIT(sim->files.memin,		 sim);
	SIMFILE_INIT(sim->files.diskin,		 sim);
	SIMFILE_INIT(sim->files.irq2in,		 sim);
	SIMFILE_INIT(sim->files.memout,		 sim);
	SIMFILE_INIT(sim->files.regout,		 sim);
	SIMFILE_INIT(sim->files.trace,		 sim);
	SIMFILE_INIT(sim->files.hwregtrace,  sim);
	SIMFILE_INIT(sim->files.cycles,		 sim);
	SIMFILE_INIT(sim->files.leds,		 sim);
	SIMFILE_INIT(sim->files.display7seg, sim);
	SIMFILE_INIT(sim->files.diskout,     sim);
	SIMFILE_INIT(sim->files.monitor,     sim);

	// Allocate memory.
	sim->mem = (SimulatorMemory)calloc(MEMORY_SIZE, sizeof(MemoryWord));
	if (NULL == sim->mem) {
		sim->status = MEMORY_ALLOCATION_ERROR;
		return;
	}

	// Allocate monitor buffer.
	sim->monitor = (SimulatorMonitor)malloc(sizeof(SimulatorMonitor));
	if (NULL == sim->monitor) {
		sim->status = MEMORY_ALLOCATION_ERROR;
		return;
	}

	// Allocate hard disk.
	sim->hdsk = (SimulatorHardDisk)calloc(HD_NUM_OF_SECTORS * HD_SECTOR_SIZE, sizeof(MemoryWord));
	if (NULL == sim->hdsk) {
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
	char* act_ext  = (char*)malloc(MAX_FILENAME_SIZE);
	char* exp_ext  = (char*)malloc(MAX_FILENAME_SIZE);

	splitFileExtention(act_file, act_name, act_ext);
	splitFileExtention(exp_file, exp_name, exp_ext);

	// Check file name.
	if (strcmp(act_name, exp_name)) {
		printf("Incorrect filename. Expected %s but got %s\n", exp_name, act_name);
		sim->status = FILE_BAD_NAME;
	}

	// Check file extension.
	if (strcmp(act_ext, exp_ext)) {
		printf("Bad extension. Expected %s.%s but got %s.%s\n", exp_name, exp_ext, act_name, act_ext);
		sim->status = FILE_BAD_EXTENSION;
	}

	// Free allocated memory.
	free(act_name);
	free(exp_name);
	free(act_ext);
	free(exp_ext);
}

void ParseCLI(int argc, char* argv[], Simulator* sim) {

	if (argc != (NUM_OF_CLI_ARGS + 1)) {
		printf("Incorrect number of arguments.\nExpected %0d | Actual: %0d\n", NUM_OF_CLI_ARGS , argc - 1);

		// Return an error code.
		sim->status = INCORRECT_CLI_ARGUMENTS;
		return;
	}

	// Open the files.
	SIMFILE_OPEN(sim->files.memin,		 argv[1 ], RAM_INPUT_FILE,				"r", sim);
	SIMFILE_OPEN(sim->files.diskin,		 argv[2 ], HDISK_INPUT_FILE,			"r", sim);
	SIMFILE_OPEN(sim->files.irq2in,		 argv[3 ], EXTERNAL_INT_FILE,			"r", sim);
	SIMFILE_OPEN(sim->files.memout,		 argv[4 ], RAM_OUTPUT_FILE,				"w", sim);
	SIMFILE_OPEN(sim->files.regout,		 argv[5 ], REGISTER_OUTPUT_FILE,		"w", sim);
	SIMFILE_OPEN(sim->files.trace,		 argv[6 ], TRACE_OUTPUT_FILE,			"w", sim);
	SIMFILE_OPEN(sim->files.hwregtrace,  argv[7 ], HW_REGISTERS_OUTPUT_FILE,	"w", sim);
	SIMFILE_OPEN(sim->files.cycles,		 argv[8 ], CYCLE_OUTPUT_FILE,			"w", sim);
	SIMFILE_OPEN(sim->files.leds,		 argv[9 ], LEDS_OUTPUT_FILE,			"w", sim);
	SIMFILE_OPEN(sim->files.display7seg, argv[10], SEGMENT_DISPLAY_OUTPUT_FILE, "w", sim);
	SIMFILE_OPEN(sim->files.diskout,	 argv[11], HDISK_OUTPUT_FILE,			"w", sim);
	SIMFILE_OPEN(sim->files.monitor,	 argv[12], MONITOR_OUTPUT_FILE,			"w", sim);
}

void InitializeMemories(Simulator* sim) {
	char line[MAX_MEM_LINE_LENGTH + 1];
	int  address = 0;
	int  value   = 0;

	// Initialize all the registers of the simulator.
	for (int i = 0; i < NUM_OF_REGISTERS; i++) {
		sim->regs[i] = REGISTER_DEFAULT;
	}

	for (int i = 0; i < NUM_OF_IO_REGISTERS; i++) {
		sim->io_regs[i] = REGISTER_DEFAULT;
	}

	// Initialize memory from file.
	while (!feof(sim->files.memin->handle)) {

		// Read the memory line.
		fgets(line, MAX_MEM_LINE_LENGTH + 1, sim->files.memin->handle);

		// Read the \n.
		fgetc(sim->files.memin->handle);

		// Covert to number and store in memory.
		(void)sscanf(line, "%X", &value);
		sim->mem[address++].word = value;
	}
}

void PrintMemory(Simulator* sim) {
	char line[MAX_MEM_LINE_LENGTH + 2];
	char line_format[MAX_MEM_LINE_LENGTH + 4];
	(void)sprintf(line_format + 2, "%0dX\n", MAX_MEM_LINE_LENGTH);
	line_format[0] = '%';
	line_format[1] = '0';

	// Check if the file is closed.
	if (feof(sim->files.memout->handle)) {
		sim->status = FILE_CLOSED;
		return;
	}

	// Write all the memory to the output file.
	for (int address = 0; address < MEMORY_SIZE; address++) {

		// Convert the memory word to a string line.
		sprintf(line, line_format, sim->mem[address].word);

		// Override case for last line.
		if (MEMORY_SIZE - 1 == address) {
			(void)sprintf(line_format + 2, "%0dX", MAX_MEM_LINE_LENGTH);
			line_format[0] = '%';
			line_format[1] = '0';
			sprintf(line, line_format, sim->mem[address].word);
		}

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
	for (RegisterOpcode i = REGISTER_RESULT_VALUE; i < REGISTER_RETURN_ADDRESS; i++) {
		fprintf(sim->files.regout->handle, "%08X\n", sim->regs[i]);
	}
	fprintf(sim->files.regout->handle, "%08X", sim->regs[REGISTER_RETURN_ADDRESS]);
}

void PrintCycles(Simulator* sim) {

	// Check if the file is closed.
	if (feof(sim->files.cycles->handle)) {
		sim->status = FILE_CLOSED;
		return;
	}

	fprintf(sim->files.cycles->handle, "%0d", sim->cycles);
}

void PrintHardDisk(Simulator* sim) {
	// Check if the file is closed.
	if (feof(sim->files.diskout->handle)) {
		sim->status = FILE_CLOSED;
		return;
	}

	// Print each word in each sector of the hard disk.
	for (int sector_index = 0; sector_index < HD_NUM_OF_SECTORS; sector_index++) {
		for (int word_index = 0; word_index < HD_SECTOR_SIZE; word_index++) {
			fprintf(sim->files.diskout->handle, "%05X\n", (*sim->hdsk)[sector_index][word_index].word);
		}
	}
}

void PrintMonitor(Simulator* sim) {
	// Check if the file is closed.
	if (feof(sim->files.monitor->handle)) {
		sim->status = FILE_CLOSED;
		return;
	}

	for (int row = 0; row < MONITOR_HEIGHT; row++) {

		// Print a column of monitor values.
		for (int col = 0; col < MONITOR_WIDTH; col++) {
			fprintf(sim->files.monitor->handle, "%02X ", sim->monitor[row][col]);
		}

		// Don't add newline at the last row.
		if (MONITOR_HEIGHT - 1 != row) {
			fprintf(sim->files.monitor->handle, "\n");
		}
	}
}

void FinalizeSimulation(Simulator* sim) {

	// Close all the files.
	CLOSE_FILE(sim->files.memin->handle);
	CLOSE_FILE(sim->files.diskin->handle);
	CLOSE_FILE(sim->files.irq2in->handle);
	CLOSE_FILE(sim->files.memout->handle);
	CLOSE_FILE(sim->files.regout->handle);
	CLOSE_FILE(sim->files.trace->handle);
	CLOSE_FILE(sim->files.hwregtrace->handle);
	CLOSE_FILE(sim->files.cycles->handle);
	CLOSE_FILE(sim->files.leds->handle);
	CLOSE_FILE(sim->files.display7seg->handle);
	CLOSE_FILE(sim->files.diskout->handle);
	CLOSE_FILE(sim->files.monitor->handle);

	// Free the simulation handles.
	if (NULL != sim->files.memin      ) { free(sim->files.memin      ); }
	if (NULL != sim->files.diskin     ) { free(sim->files.diskin     ); }
	if (NULL != sim->files.irq2in     ) { free(sim->files.irq2in     ); }
	if (NULL != sim->files.memout     ) { free(sim->files.memout     ); }
	if (NULL != sim->files.regout     ) { free(sim->files.regout     ); }
	if (NULL != sim->files.trace      ) { free(sim->files.trace      ); }
	if (NULL != sim->files.hwregtrace ) { free(sim->files.hwregtrace ); }
	if (NULL != sim->files.cycles     ) { free(sim->files.cycles     ); }
	if (NULL != sim->files.leds       ) { free(sim->files.leds       ); }
	if (NULL != sim->files.display7seg) { free(sim->files.display7seg); }
	if (NULL != sim->files.diskout    ) { free(sim->files.diskout    ); }
	if (NULL != sim->files.monitor    ) { free(sim->files.monitor    ); }

	// Free the memory.
	if (NULL != sim->mem)     { free(sim->mem); }
	if (NULL != sim->monitor) { free(sim->monitor); }
	if (NULL != sim->hdsk)    { free(sim->hdsk); }
}

int main(int argc, char* argv[]) {
	Simulator sim;

	// Initialize simulator.
	InitializeSimulator(&sim);

	// Memory allocation error, free memory that was allocated.
	if (NO_ERROR == sim.status) {

		// Check the command line arguments.
		ParseCLI(argc, argv, &sim);

		// General idea:
		// Run the main loop of the CPU (simulated) with the inputs from the compiler.
		if (NO_ERROR == sim.status) {
			InitializeMemories(&sim);
			mainLoop(&sim);

			// Outputs.
			PrintMemory(&sim);
			PrintRegisters(&sim);
			PrintCycles(&sim);
			PrintHardDisk(&sim);
			PrintMonitor(&sim);
		}
	}

	FinalizeSimulation(&sim);

	// Check if simulation finished correctly (by the book).
	if (HALT_SIMULATOR == sim.status) { return (NO_ERROR); }
	return (sim.status);
}