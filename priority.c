#include <stdio.h>

struct Process
{
    int pid;             // Process ID
    int burst_time;      // Burst time of the process
    int priority;        // Priority of the process
    int waiting_time;    // Waiting time of the process
    int turnaround_time; // Turnaround time of the process
};

void priorityScheduling(struct Process processes[], int n)
{
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Sort the processes based on priority (higher number = higher priority)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].priority < processes[j].priority)
            {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Calculate waiting time for each process
    processes[0].waiting_time = 0; // First process always has zero waiting time

    for (int i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Display process information
    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].priority, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Calculate and display average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input burst time and priority for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("Enter burst time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process P%d (higher number = higher priority): ", processes[i].pid);
        scanf("%d", &processes[i].priority);
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    priorityScheduling(processes, n);

    return 0;
}

// output
// Enter the number of processes: 4
// Enter burst time for process P1: 5
// Enter priority for process P1 (higher number = higher priority): 2
// Enter burst time for process P2: 8
// Enter priority for process P2 (higher number = higher priority): 1
// Enter burst time for process P3: 12
// Enter priority for process P3 (higher number = higher priority): 4
// Enter burst time for process P4: 6
// Enter priority for process P4 (higher number = higher priority): 3

// Process Priority Burst Time Waiting Time Turnaround Time
// P3 4 12 0 12
// P4 3 6 12 18
// P1 2 5 18 23
// P2 1 8 23 31

// Average Waiting Time: 13.25
// Average Turnaround Time: 21.00
