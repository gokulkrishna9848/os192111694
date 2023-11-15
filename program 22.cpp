#include <stdio.h>

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

// Function to initialize the memory blocks
void initializeMemory(struct MemoryBlock memory[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        memory[i].id = i + 1;
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

// Function to display the memory blocks
void displayMemory(struct MemoryBlock memory[], int numBlocks) {
    printf("Memory Blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: Size: %d, Allocated: %s\n", memory[i].id, memory[i].size,
            memory[i].allocated ? "Yes" : "No");
    }
}

// Function to allocate memory using best fit algorithm
void bestFit(struct MemoryBlock memory[], int numBlocks, int processSize) {
    int bestFitIndex = -1;
    int smallestBlockSize = -1;

    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (bestFitIndex == -1 || memory[i].size < smallestBlockSize) {
                bestFitIndex = i;
                smallestBlockSize = memory[i].size;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = 1;
        printf("Process of size %d allocated to Block %d\n", processSize, memory[bestFitIndex].id);
    } else {
        printf("No suitable block found for process of size %d\n", processSize);
    }
}

int main() {
    int numBlocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    struct MemoryBlock memory[numBlocks];
    initializeMemory(memory, numBlocks);

    for (int i = 0; i < numBlocks; i++) {
        printf("Enter size of Block %d: ", i + 1);
        scanf("%d", &memory[i].size);
    }

    while (1) {
        int processSize;
        printf("Enter process size (or -1 to exit): ");
        scanf("%d", &processSize);

        if (processSize == -1) {
            break;
        }

        bestFit(memory, numBlocks, processSize);
        displayMemory(memory, numBlocks);
    }

    return 0;
}