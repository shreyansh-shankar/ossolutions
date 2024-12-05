#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int main()
{
    int n, m, i, j, k;

    // Input number of processes and resources
    n = 5; // Number of processes
    m = 3; // Number of resources

    // Max matrix (maximum demand of each process)
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}};

    // Allocation matrix (current resource allocation)
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};

    // Available resources
    int available[MAX_RESOURCES] = {3, 3, 2};

    // Need matrix (max - allocation)
    int need[MAX_PROCESSES][MAX_RESOURCES];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Finish array to track which processes have completed
    bool finish[MAX_PROCESSES] = {false};

    // Work array to keep track of the available resources
    int work[MAX_RESOURCES];
    for (i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    // Safe sequence
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Banker's algorithm
    while (count < n)
    {
        bool found = false;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            printf("The system is in an unsafe state.\n");
            return -1;
        }
    }

    // Output safe sequence
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
    {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}

// output
// The system is in a safe state.
// Safe sequence is: P1 P3 P4 P0 P2
