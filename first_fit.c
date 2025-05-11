#include <stdio.h>
#include <stdlib.h>

int main()
{
    int np, nb;
    printf("Enter the number of processes: ");
    scanf("%d", &np);

    printf("Enter number of blocks: ");
    scanf("%d", &nb);

    // int b[nb];
    // int p[np];
    // int frag[np];
    // int bn[np];
    // int bf[nb];

    int *b = (int *)malloc(nb * sizeof(int));
    int *bf = (int *)malloc(nb * sizeof(int));
    int *p = (int *)malloc(np * sizeof(int));
    int *frag = (int *)malloc(np * sizeof(int));
    int *bn = (int *)malloc(np * sizeof(int));

    int i, j;
    for (i = 0; i < np; i++)
        frag[i] = 0;
    for (i = 0; i < nb; i++)
        bf[i] = 0;

    for (i = 0; i < nb; i++)
    {
        printf("Enter the size of block %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    printf("Enter the process sizes:\n");
    for (i = 0; i < np; i++)
    {
        printf("Process %d size: ", i + 1);
        scanf("%d", &p[i]);
        bn[i] = -1; // Initialize as not allocated
    }

    // First Fit
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nb; j++)
        {
            if (bf[j] == 0 && b[j] >= p[i])
            {
                bn[i] = j;
                bf[j] = 1;
                frag[i] = b[j] - p[i];
                break;
            }
        }
    }

    // Display
    printf("\nProcess_No.\tProcess_Size\tBlock_No.\tBlock_Size\tFragmentation\n");
    for (i = 0; i < np; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, p[i]);
        if (bn[i] != -1)
        {
            printf("%d\t\t%d\t\t%d\n", bn[i] + 1, b[bn[i]], frag[i]);
        }
        else
        {
            printf("Not Allocated\t0\t\t0\n");
        }
    }

    return 0;
}
