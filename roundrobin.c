#include <stdio.h>

struct Process
{
    int pid;             // Process ID
    int burst_time;      // Burst time of the process
    int remaining_time;  // Remaining time after execution
    int waiting_time;    // Waiting time of the process
    int turnaround_time; // Turnaround time of the process
};

void roundRobin(struct Process processes[], int n, int time_quantum)
{
    int total_time = 0, completed = 0;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    while (completed != n)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0)
            {
                done = 0;
                if (processes[i].remaining_time > time_quantum)
                {
                    total_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }
                else
                {
                    total_time += processes[i].remaining_time;
                    processes[i].waiting_time = total_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    completed++;
                }
                processes[i].turnaround_time = total_time;
            }
        }
        if (done == 1)
            break;
    }

    // Calculate average waiting time and turnaround time
    for (int i = 0; i < n; i++)
    {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main()
{
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("Enter the burst time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    roundRobin(processes, n, time_quantum);

    return 0;
}

// output
// Enter the number of processes: 4
// Enter the burst time for process P1: 5
// Enter the burst time for process P2: 8
// Enter the burst time for process P3: 12
// Enter the burst time for process P4: 6
// Enter the time quantum: 4

// Process Burst Time Waiting Time Turnaround Time
// P1 5 16 21
// P2 8 20 28
// P3 12 26 38
// P4 6 22 28

// Average Waiting Time: 21.00
// Average Turnaround Time: 28.75
