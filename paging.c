#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 256
#define TOTAL_FRAMES 16

void simulatePaging(int pages[], int numPages, int pageTable[], int numFrames) {
    int i, page, frame, logicalAddress, physicalAddress;

    printf("\nLogical Address -> Physical Address Mapping:\n");
    printf("------------------------------------------------\n");

    for (i = 0; i < numPages; ++i)
    {
        page = pages[i];

        // Check if the page is valid
        if (page < 0 || page >= numFrames)
        {
            printf("Page %d is invalid!\n", page);
            continue;
        }

        frame = pageTable[page];
        if (frame == -1)
        {
            printf("Page %d is not loaded in any frame!\n", page);
            continue;
        }

        logicalAddress = page * FRAME_SIZE;
        physicalAddress = frame * FRAME_SIZE;

        printf("Logical Address %d -> Physical Address %d\n", logicalAddress, physicalAddress);
    }
}

int main() {
    int numPages, numFrames, i;

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pages[numPages];
    printf("Enter the page numbers (0 to %d): ", TOTAL_FRAMES - 1);
    for (i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames in physical memory: ");
    scanf("%d", &numFrames);

    if (numFrames > TOTAL_FRAMES)
    {
        printf("Number of frames cannot exceed %d\n", TOTAL_FRAMES);
        return -1;
    }

    int pageTable[TOTAL_FRAMES];
    for (i = 0; i < TOTAL_FRAMES; i++)
    {
        pageTable[i] = -1;
    }

    printf("Enter the frame number for each page (or -1 for not loaded):\n");
    for (i = 0; i < numFrames; i++)
    {
        int page;
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    simulatePaging(pages, numPages, pageTable, numFrames);

    return 0;
}

// output
// Enter the number of pages: 4
// Enter the page numbers (0 to 15): 0 1 2 3
// Enter the number of frames in physical memory: 4
// Enter the frame number for each page (or -1 for not loaded):
// Page 0 -> Frame: 3
// Page 1 -> Frame: 5
// Page 2 -> Frame: 8
// Page 3 -> Frame: 10
// Logical Address -> Physical Address Mapping:
// ------------------------------------------------
// Logical Address 0 -> Physical Address 768
// Logical Address 256 -> Physical Address 1280
// Logical Address 512 -> Physical Address 2048
// Logical Address 768 -> Physical Address 2560
