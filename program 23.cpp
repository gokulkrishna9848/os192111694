#include <stdio.h>


struct MemoryBlock {
    int id;
    int size;
    int allocated;
};

void initializeMemory(struct MemoryBlock memory[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        memory[i].id = i + 1;
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}


void displayMemory(struct MemoryBlock memory[], int numBlocks) {
    printf("Memory Blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: Size: %d, Allocated: %s\n", memory[i].id, memory[i].size,
            memory[i].allocated ? "Yes" : "No");
    }
}


void firstFit(struct MemoryBlock memory[], int numBlocks, int processSize) {
    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].allocated = 1;
            printf("Process of size %d allocated to Block %d\n", processSize, memory[i].id);
            return;
        }
    }
    
    printf("No suitable block found for process of size %d\n", processSize);
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

        firstFit(memory, numBlocks, processSize);
        displayMemory(memory, numBlocks);
    }

    return 0;
}