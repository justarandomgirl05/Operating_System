#include <stdio.h>

int main()
{
    int nf, np;
    printf("Enter number of frames:\n");
    scanf("%d", &nf);
    printf("Enter number of pages:\n");
    scanf("%d", &np);

    int *f = (int *)malloc(nf * sizeof(int));
    int *p = (int *)malloc(np * sizeof(int));
    int *time = (int *)malloc(nf * sizeof(int));

    int i, j, fault = 0, count = 0;

    // Initializing frame values to -1
    for (i = 0; i < nf; i++)
    {
        f[i] = -1;
        time[i] = 0;
    }

    printf("Enter page references:\n");
    for (i = 0; i < np; i++)
    {
        scanf("%d", &p[i]);
    }

    printf("\nPage\t");
    for (i = 0; i < nf; i++)
    {
        printf("F%d\t", i + 1);
    }
    printf("\n");

    for (i = 0; i < np; i++)
    {
        int flag1 = 0, flag2 = 0;

        // Check if page is already in frame
        for (j = 0; j < nf; j++)
        {
            if (f[j] == p[i])
            {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page not found in frame
        if (flag1 == 0)
        {
            for (j = 0; j < nf; j++)
            {
                if (f[j] == -1)
                {
                    count++;
                    fault++;
                    f[j] = p[i];
                    time[j] = count;
                    flag2 = 1;
                    break;
                }
            }
        }

        // Replace LRU page if no empty frame found
        if (flag2 == 0)
        {
            int min = time[0], pos = 0;
            for (j = 1; j < nf; j++)
            {
                if (time[j] < min)
                {
                    min = time[j];
                    pos = j;
                }
            }
            count++;
            fault++;
            f[pos] = p[i];
            time[pos] = count;
        }

        // Display frame status
        printf("%d\t", p[i]);
        for (j = 0; j < nf; j++)
        {
            if (f[j] != -1)
                printf("%d\t", f[j]);
            else
                printf("-1\t");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", fault);

    return 0;
}
