#include <stdio.h>

struct Process
{
    int pid;            // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int waitingTime;    // Waiting time
    int turnaroundTime; // Turnaround time
    int completed;      // Process completion status
};

void findWaitingTime(struct Process proc[], int n)
{
    int completedProcesses = 0, currentTime = 0, minBurstTimeIndex;
    int minBurstTime, finishTime;
    int totalWaitingTime = 0;

    while (completedProcesses != n)
    {
        minBurstTime = 10000;
        minBurstTimeIndex = -1;

        // Find process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && proc[i].completed == 0)
            {
                if (proc[i].burstTime < minBurstTime)
                {
                    minBurstTime = proc[i].burstTime;
                    minBurstTimeIndex = i;
                }
            }
        }

        if (minBurstTimeIndex != -1)
        {
            currentTime += proc[minBurstTimeIndex].burstTime;
            finishTime = currentTime;
            proc[minBurstTimeIndex].turnaroundTime = finishTime - proc[minBurstTimeIndex].arrivalTime;
            proc[minBurstTimeIndex].waitingTime = proc[minBurstTimeIndex].turnaroundTime - proc[minBurstTimeIndex].burstTime;
            proc[minBurstTimeIndex].completed = 1;
            completedProcesses++;
        }
        else
        {
            currentTime++;
        }
    }
}

void findTurnaroundTime(struct Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        proc[i].turnaroundTime = proc[i].burstTime + proc[i].waitingTime;
    }
}

void findAvgTime(struct Process proc[], int n)
{
    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / (float)n);
    printf("\nAverage Turnaround Time: %.2f", (float)totalTurnaroundTime / (float)n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burstTime);
        proc[i].completed = 0;
    }

    findAvgTime(proc, n);

    return 0;
}

// output
// Enter the number of processes: 4
// Enter arrival time for process 1: 0
// Enter burst time for process 1: 8
// Enter arrival time for process 2: 1
// Enter burst time for process 2: 4
// Enter arrival time for process 3: 2
// Enter burst time for process 3: 9
// Enter arrival time for process 4: 3
// Enter burst time for process 4: 5

// Process Arrival Time    Burst Time      Waiting Time    Turnaround Time
// 1               0               8               0               8
// 2               1               4               7               11
// 3               2               9               15              24
// 4               3               5               9               14

// Average Waiting Time: 7.75
// Average Turnaround Time: 14.25
