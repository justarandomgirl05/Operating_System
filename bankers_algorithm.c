#include <stdio.h>

int main()
{
    // Step 1: Define data
    int np, nr, i, j, k = 0, flag;
    int allocation[10][10], max[10][10], need[10][10];
    int available[10], finish[10], safeseq[10];

    // Step 2: Accept data from user
    printf("Enter the number of processes: ");
    scanf("%d", &np);
    printf("Enter the number of resources: ");
    scanf("%d", &nr);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Max matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources:\n");
    for (j = 0; j < nr; j++)
        scanf("%d", &available[j]);

    for (i = 0; i < np; i++)
        finish[i] = 0;

    // Step 3: Calculate need matrix
    for (i = 0; i < np; i++)
        for (j = 0; j < nr; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Step 4: Check for deadlock
    int count = 0;
    while (count < np)
    {
        flag = 0;
        for (i = 0; i < np; i++)
        {
            if (finish[i] == 0)
            {
                int canAllocate = 1;
                for (j = 0; j < nr; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (j = 0; j < nr; j++)
                        available[j] += allocation[i][j];
                    finish[i] = 1;
                    safeseq[k++] = i;
                    count++;
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0)
            break;
    }

    // Step 5: Check status
    if (count == np)
    {
        printf("System is in a Safe State.\nSafe Sequence is: ");
        for (i = 0; i < np; i++)
            printf("P%d ", safeseq[i]);
        printf("\n");
    }
    else
    {
        printf("System is in Deadlock. No Safe Sequence exists.\n");
    }
    return 0;
}
