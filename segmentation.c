#include <stdio.h>

typedef struct
{
    int base;  // Base address of the segment
    int limit; // Limit of the segment
} Segment;

void simulateSegmentation(Segment segments[], int numSegments)
{
    int logicalSegment, logicalOffset, physicalAddress;

    printf("\nEnter the logical address (segment number and offset): ");
    scanf("%d %d", &logicalSegment, &logicalOffset);

    // Validate segment number
    if (logicalSegment >= numSegments || logicalSegment < 0)
    {
        printf("Error: Invalid segment number.\n");
        return;
    }

    // Validate offset
    if (logicalOffset >= segments[logicalSegment].limit || logicalOffset < 0)
    {
        printf("Error: Offset exceeds segment limit.\n");
        return;
    }

    // Calculate physical address
    physicalAddress = segments[logicalSegment].base + logicalOffset;
    printf("Physical Address: %d\n", physicalAddress);
}

int main()
{
    int numSegments, i;

    printf("Enter the number of segments: ");
    scanf("%d", &numSegments);

    Segment segments[numSegments];

    // Input segment table
    printf("Enter base address and limit for each segment:\n");
    for (i = 0; i < numSegments; i++)
    {
        printf("Segment %d: ", i);
        scanf("%d %d", &segments[i].base, &segments[i].limit);
    }

    char choice;
    do
    {
        simulateSegmentation(segments, numSegments);
        printf("Do you want to enter another logical address? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

// output
// Enter the number of segments: 3
// Enter base address and limit for each segment:
// Segment 0: 100 50
// Segment 1: 200 60
// Segment 2: 300 40
// Enter the logical address (segment number and offset): 1 20
// Physical Address: 220
// Enter the logical address (segment number and offset): 2 50
// Error: Offset exceeds segment limit.
