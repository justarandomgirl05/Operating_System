#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nb, np, i, j, index;

    printf("Enter number of blocks: ");
    scanf("%d", &nb);
    printf("Enter number of processes: ");
    scanf("%d", &np);

    // int b[nb], bf[nb], p[np], frag[np], bn[np];
    int *b = (int *)malloc(nb * sizeof(int));
    int *bf = (int *)malloc(nb * sizeof(int));
    int *p = (int *)malloc(np * sizeof(int));
    int *frag = (int *)malloc(np * sizeof(int));
    int *bn = (int *)malloc(np * sizeof(int));

    printf("Enter the size of each block: ");
    for (i = 0; i < nb; i++)
    {
        scanf("%d", &b[i]);
        bf[i] = 0; // Initialize block flags
    }

    printf("Enter the size of each process: ");
    for (i = 0; i < np; i++)
    {
        scanf("%d", &p[i]);
        frag[i] = 0; // Initialize fragmentation
        bn[i] = -1;  // Initialize block number (-1 for unallocated)
    }

    for (i = 0; i < np; i++)
    {
        int smallest = 1000; // Use INT_MAX for initialization
        index = -1;          // Reset index for each process

        for (j = 0; j < nb; j++)
        {
            if (bf[j] == 0 && b[j] >= p[i])
            { // Check if block is free and large enough
                if (b[j] < smallest)
                { // Find the smallest suitable block
                    smallest = b[j];
                    index = j;
                }
            }
        }

        if (index != -1) // If a suitable block is found
        {
            bf[index] = 1;             // Mark the block as allocated(used)
            bn[i] = index;             // Assign block to process
            frag[i] = smallest - p[i]; // Calculate fragmentation
        }
    }

    printf("best Fit Algorithm :\n");
    printf("process No \t process size \t block No \t Block size \t Fragment of process\t \n ");
    for (i = 0; i < np; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", i + 1, p[i], bn[i] + 1, b[bn[i]], frag[i]);
    }

    return 0;
}
