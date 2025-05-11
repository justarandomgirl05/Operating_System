#include <stdio.h>

int main()
{
    int nf, np, p[30], f[3], fault = 0, hit = 0, pos = 0, flag, i, j;

    printf("Enter the number of frames: ");
    scanf("%d", &nf);
    printf("Enter the number of pages: ");
    scanf("%d", &np);

    printf("Enter the page reference string (separate values with spaces): ");
    for (i = 0; i < np; i++)
    {
        scanf("%d", &p[i]);
    }

    for (i = 0; i < nf; i++)
    {
        f[i] = -1;
    }

    printf("\nFrame Status After Each Reference:\n");

    for (i = 0; i < np; i++)
    {
        flag = 0;

        for (j = 0; j < nf; j++)
        {
            if (f[j] == p[i]) // This inner loop checks if the current page (p[i]) is already present in one of the frames (f[j]).
            {
                hit++;
                flag = 1;
                break;
            }
        }

        // page fault handling
        if (flag == 0)
        {
            f[pos] = p[i]; // We load the page into the frame at position pos.
            pos++;

            if (pos == nf)
            {
                pos = 0;
            }

            fault++;
        }

        // Print the Frame Status After Each Page Reference
        for (j = 0; j < nf; j++)
        {
            if (f[j] != -1)
            {
                printf("F%d: %d  ", j, f[j]);
            }
            else
            {
                printf("F%d: -1  ", j);
            }
        }

        if (flag == 0)
        {
            printf(" <- Page Fault");
        }
        else
        {
            printf(" <- Page Hit");
        }

        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", fault);
    printf("Total Page Hits: %d\n", hit);

    float hit_ratio = (float)hit / np;
    float miss_ratio = (float)fault / np;
    printf("Hit Ratio: %.2f\n", hit_ratio);
    printf("Miss Ratio: %.2f\n", miss_ratio);

    return 0;
}
