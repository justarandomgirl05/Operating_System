#include <stdio.h>
#include <stdlib.h>

// Structure to hold process details
typedef struct
{
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int remaining;  // Remaining Burst Time
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
} Process;

void roundRobinScheduling(Process p[], int n, int quantum)
{
    int time = 0, completed = 0;

    while (completed < n)
    {
        int executed = 0;

        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining > 0 && p[i].arrival <= time)
            {
                if (p[i].remaining > quantum)
                {
                    time += quantum;
                    p[i].remaining -= quantum;
                }
                else
                {
                    time += p[i].remaining;
                    p[i].completion = time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    p[i].remaining = 0;
                    completed++;
                }
                executed = 1;
            }
        }

        if (!executed)
        {
            time++;
        }
    }
}

void printTable(Process p[], int n)
{
    printf("\nProcess | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("   P%d    |      %d      |     %d     |       %d       |       %d       |       %d\n",
               p[i].pid, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main()
{
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Process p[n];
    Process *p = (Process *)malloc(n * sizeof(Process));

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Process %d - Arrival Time: ", p[i].pid);
        scanf("%d", &p[i].arrival);
        printf("Process %d - Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Execute Round Robin Scheduling
    roundRobinScheduling(p, n, quantum);

    // Print the results
    printTable(p, n);

    return 0; // Add this return statement to properly end the main function
}
