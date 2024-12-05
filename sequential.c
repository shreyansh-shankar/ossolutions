#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100

void initializeDisk(bool disk[], int size)
{
    for (int i = 0; i < size; i++)
    {
        disk[i] = false; // Mark all blocks as free
    }
}

bool allocateFile(bool disk[], int size, int startBlock, int numBlocks)
{
    if (startBlock + numBlocks > size)
    {
        return false; // Not enough space
    }

    for (int i = startBlock; i < startBlock + numBlocks; i++)
    {
        if (disk[i])
        {
            return false; // Block already allocated
        }
    }

    // Allocate blocks
    for (int i = startBlock; i < startBlock + numBlocks; i++)
    {
        disk[i] = true;
    }
    return true;
}

void displayDisk(bool disk[], int size)
{
    printf("\nDisk Status (0 = Free, 1 = Allocated):\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

int main()
{
    int diskSize = MAX_BLOCKS;
    bool disk[MAX_BLOCKS];
    int startBlock, numBlocks;
    char choice;

    initializeDisk(disk, diskSize);

    printf("Sequential File Allocation Simulation\n");
    printf("Disk Size: %d blocks\n", diskSize);

    do
    {
        printf("\nEnter starting block and number of blocks to allocate: ");
        scanf("%d %d", &startBlock, &numBlocks);

        if (allocateFile(disk, diskSize, startBlock, numBlocks))
        {
            printf("File allocated successfully from block %d to %d.\n", startBlock, startBlock + numBlocks - 1);
        }
        else
        {
            printf("File allocation failed! Check if the blocks are available or within range.\n");
        }

        displayDisk(disk, diskSize);

        printf("Do you want to allocate another file? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

// output
// Sequential File Allocation Simulation
// Disk Size: 100 blocks

// Enter starting block and number of blocks to allocate: 10 5
// File allocated successfully from block 10 to 14.

// Disk Status (0 = Free, 1 = Allocated):
// 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 ... (rest are 0)
// Enter starting block and number of blocks to allocate: 12 3
// File allocation failed! Check if the blocks are available or within range.

// Disk Status (0 = Free, 1 = Allocated):
// 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 0 0 0 ... (rest are 0)
