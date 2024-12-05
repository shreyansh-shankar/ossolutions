#include <stdio.h>

int isPresent(int frames[], int capacity, int page)
{
    for (int i = 0; i < capacity; i++)
    {
        if (frames[i] == page)
        {
            return 1;
        }
    }
    return 0;
}

int findOptimal(int pages[], int frames[], int capacity, int current, int n)
{
    int farthest = current, index = -1;
    for (int i = 0; i < capacity; i++)
    {
        int j;
        for (j = current + 1; j < n; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n)
        {
            return i;
        }
    }
    return (index == -1) ? 0 : index;
}

void optimalPageReplacement(int pages[], int n, int capacity)
{
    int frames[capacity];
    int faults = 0;

    for (int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
    }

    printf("\nFrames Status:\n");
    for (int i = 0; i < n; i++)
    {
        if (!isPresent(frames, capacity, pages[i]))
        {
            faults++;
            if (i < capacity)
            {
                frames[i] = pages[i];
            }
            else
            {
                int pos = findOptimal(pages, frames, capacity, i, n);
                frames[pos] = pages[i];
            }
        }

        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] != -1)
            {
                printf("%d ", frames[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);
}

int main()
{
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    optimalPageReplacement(pages, n, capacity);

    return 0;
}

// output
// Enter the number of pages: 8
// Enter the page reference string: 7 0 1 2 0 3 0 4
// Enter the number of frames: 3
// Frames Status:
// 7 - -
// 7 0 -
// 7 0 1
// 2 0 1
// 2 0 1
// 3 0 1
// 3 0 1
// 4 0 1

// Total Page Faults: 6
