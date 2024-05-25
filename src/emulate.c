#include <stdlib.h>
#include <stdio.h>

#define MEMORY_SIZE 1024 // Define a suitable memory size

unsigned int memory[MEMORY_SIZE]; // Memory array to hold the binary object code

void load_binary_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    size_t read_size = fread(memory, sizeof(unsigned int), MEMORY_SIZE, file);
    if (read_size == 0 && !feof(file)) {
        perror("Error reading file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    fclose(file);
}

void emulate() {
    // Placeholder for the emulation logic
    // This should include the execution of instructions stored in the memory array
    // Example: Iterate through the memory array and execute instructions
    for (size_t i = 0; i < MEMORY_SIZE; i++) {
        // Example: Print memory content as a placeholder for actual execution
        printf("Memory[%zu]: 0x%08x\n", i, memory[i]);
    }
}

void save_results(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < MEMORY_SIZE; i++) {
        fprintf(file, "Memory[%zu]: 0x%08x\n", i, memory[i]);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <file_in> [file_out]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *input_file = argv[1];
    const char *output_file = (argc == 3) ? argv[2] : NULL;

    load_binary_file(input_file);
    emulate();

    if (output_file) {
        save_results(output_file);
    } else {
        // Print to stdout
        for (size_t i = 0; i < MEMORY_SIZE; i++) {
            printf("Memory[%zu]: 0x%08x\n", i, memory[i]);
        }
    }

    return 0;
}
