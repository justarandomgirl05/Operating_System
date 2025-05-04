#include <stdio.h>
#include <stdlib.h>

int main()
{
    int np;
    printf("Enter the total no of pages: ");
    scanf("%d", &np);

    int page_size;
    printf("Enter the page size: ");
    scanf("%d", &page_size);

    int PT[10];
    int FN;
    printf("Page Table:\n");
    for (int i = 0; i < np; i++)
    {
        printf("Enter the frame number for P%d: ", i);
        scanf("%d", &FN);
        PT[i] = FN;
    }

    int LA;
    printf("Enter the Logical Address: ");
    scanf("%d", &LA);

    int PA;
    int PN = LA / page_size;
    int offset = LA % page_size;
    if (PN >= np)
    {
        printf("Invalid Logical Address");
        return 0;
    }
    FN = PT[PN];
    PA = FN * page_size + offset;

    printf("Logical Address: %d ", LA);
    printf("\nPage Number: %d ", PN);
    printf("\nOffset:  %d", offset);
    printf("\nFrame Number:  %d", FN);
    printf("\nPhysical Address: %d", PA);
}
