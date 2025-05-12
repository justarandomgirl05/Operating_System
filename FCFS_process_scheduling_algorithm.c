#include <stdio.h>

// Structure to hold process details

typedef struct
{

    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
} Process;

void sortByArrival(Process p[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {

        for (int j = 0; j < n - i - 1; j++)
        {

            if (p[j].arrival > p[j + 1].arrival)
            {

                Process temp = p[j];

                p[j] = p[j + 1];

                p[j + 1] = temp;
            }
        }
    }
}

void calculateFCFS(Process p[], int n)
{

    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < p[i].arrival)
            time = p[i].arrival;

        p[i].completion = time + p[i].burst;

        p[i].turnaround = p[i].completion - p[i].arrival;

        p[i].waiting = p[i].turnaround - p[i].burst;

        time = p[i].completion;
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

    int n;
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
    }

    // Sort processes based on arrival time

    sortByArrival(p, n);

    // Calculate FCFS Scheduling

    calculateFCFS(p, n);

    // Print the results

    printTable(p, n);

    return 0;
}
