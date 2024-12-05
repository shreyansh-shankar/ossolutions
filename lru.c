#include <stdio.h>

int findLRU(int time[], int n)
{
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; ++i)
    {
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void LRUPageReplacement(int pages[], int n, int frames[], int capacity)
{
    int time[capacity], flag1, flag2, i, j, pos, faults = 0;
    for (i = 0; i < capacity; ++i)
    {
        frames[i] = -1;
    }
    for (i = 0; i < n; ++i)
    {
        flag1 = flag2 = 0;

        // Check if the page is already in a frame
        for (j = 0; j < capacity; ++j)
        {
            if (frames[j] == pages[i])
            {
                flag1 = flag2 = 1;
                time[j] = i; // Update time for LRU
                break;
            }
        }

        // If the page is not in a frame
        if (flag1 == 0)
        {
            for (j = 0; j < capacity; ++j)
            {
                if (frames[j] == -1)
                {
                    faults++;
                    frames[j] = pages[i];
                    time[j] = i;
                    flag2 = 1;
                    break;
                }
            }
        }

        // Replace the least recently used page
        if (flag2 == 0)
        {
            pos = findLRU(time, capacity);
            frames[pos] = pages[i];
            time[pos] = i;
            faults++;
        }

        // Display the frame content
        printf("\nFrames: ");
        for (j = 0; j < capacity; ++j)
        {
            if (frames[j] != -1)
            {
                printf("%d ", frames[j]);
            }
            else
            {
                printf("-");
            }
        }
    }
    printf("\n\nTotal Page Faults: %d\n", faults);
}

int main()
{
    int n, capacity, i;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    int frames[capacity];
    LRUPageReplacement(pages, n, frames, capacity);

    return 0;
}

// output
// Enter the number of pages: 8
// Enter the page reference string: 7 0 1 2 0 3 0 4
// Enter the number of frames: 3
// Frames: 7 - -
// Frames: 7 0 -
// Frames: 7 0 1
// Frames: 2 0 1
// Frames: 2 0 1
// Frames: 3 0 1
// Frames: 3 0 1
// Frames: 4 0 1

// Total Page Faults: 6
