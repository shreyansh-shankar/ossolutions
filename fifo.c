#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int capacity)
{
    int frames[capacity], front = 0, pageFaults = 0, i, j, flag;

    // Initialize frames to -1 (empty)
    for (i = 0; i < capacity; i++)
    {
        frames[i] = -1;
    }

    printf("Page Reference String: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("\nFrames:\n");
    for (i = 0; i < n; i++)
    {
        flag = 0;

        // Check if page is already in a frame
        for (j = 0; j < capacity; j++)
        {
            if (frames[j] == pages[i])
            {
                flag = 1; // Page hit
                break;
            }
        }

        // If page fault occurs
        if (flag == 0)
        {
            frames[front] = pages[i];
            front = (front + 1) % capacity; // Move to next frame (FIFO)
            pageFaults++;

            // Print the frames
            for (j = 0; j < capacity; j++)
            {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main()
{
    int n, capacity, i;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    // Input the frame capacity
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    fifoPageReplacement(pages, n, capacity);

    return 0;
}

// Enter the number of pages: 12
// Enter the page reference string: 7 0 1 2 0 3 0 4 2 3 0 3
// Enter the number of frames: 3
// Page Reference String: 7 0 1 2 0 3 0 4 2 3 0 3

// Frames:
// 7 - -
// 7 0 -
// 7 0 1
// 2 0 1
// 2 0 1
// 2 3 1
// 2 3 0
// 4 3 0
// 4 3 2
// 4 3 2
// 4 3 2
// 4 3 2

// Total Page Faults: 8
