
#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[20], p[20], prio[20], wt[20], tat[20];

    // Input Burst Time and Priority
    for (int i = 0; i < n; i++)
    {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter Priority for Process %d: ", i + 1);
        scanf("%d", &prio[i]);
        p[i] = i + 1; // Process ID
    }

    // Sorting based on Priority (Ascending)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (prio[i] > prio[j])
            {
                int temp;

                temp = prio[i];
                prio[i] = prio[j];
                prio[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0; // First process waiting time is 0

    // Calculate Waiting Time
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate Turn Around Time
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
    }

    // Display
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], prio[i], wt[i], tat[i]);
    }

    // Calculate Average WT and TAT
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turn Around Time = %.2f\n", avg_tat);

    return 0;
}
