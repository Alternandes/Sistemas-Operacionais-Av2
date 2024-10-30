#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FRAMES 3
#define TAU 3

typedef struct {
    int pageNumber;
    int referenceBit;
    int lastUsedTime;
} PageFrame;

int main() {
    PageFrame memory[NUM_FRAMES];
    int pageReferences[] = {0, 1, 1, 2, 3, 0, 4, 1, 2, 5, 3, 4, 6};
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);
    int i, j, k = 0;
    int currentTime = 0;

    for (i = 0; i < NUM_FRAMES; i++) {
        memory[i].pageNumber = -1;
        memory[i].referenceBit = 0;
        memory[i].lastUsedTime = 0;
    }

    for (i = 0; i < numReferences; i++) {
        int pageReferenced = pageReferences[i];
        int pageFound = 0;
        currentTime++;

        for (j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNumber == pageReferenced) {
                memory[j].referenceBit = 1;
                memory[j].lastUsedTime = currentTime;
                pageFound = 1;
                printf("Página %d já está referenciada na memória\n", pageReferenced);
                break;
            }
        }

        if (!pageFound) {
            while (1) {
                if (memory[k].referenceBit == 0 && (currentTime - memory[k].lastUsedTime) > TAU) {
                    printf("Substituiu página %d\n", memory[k].pageNumber);
                    memory[k].pageNumber = pageReferenced;
                    memory[k].referenceBit = 1;
                    memory[k].lastUsedTime = currentTime;
                    break;
                } else if (memory[k].referenceBit == 0) {
                    printf("Substituiu página %d\n", memory[k].pageNumber);
                    memory[k].pageNumber = pageReferenced;
                    memory[k].referenceBit = 1;
                    memory[k].lastUsedTime = currentTime;
                    break;
                } else {
                    memory[k].referenceBit = 0;
                }
                k = (k + 1) % NUM_FRAMES;
            }
        }

        printf("Estado da memória após referência %d: ", pageReferenced);
        for (j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNumber == -1)
                printf("[ - ] ");
            else
                printf("[ %d ] ", memory[j].pageNumber);
        }
        printf("\n");
    }

    return 0;
}