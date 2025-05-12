#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int main()
{
    int n;
    printf("Enter the number of disc request: ");
    scanf("%d", &n);

    int disc_req[200];

    for (int i = 0; i < n; i++)
    {
        printf("Enter the %d track number in disk request: ", i);
        scanf("%d", &disc_req[i]);
    }

    int head;

    printf("Enter the initial track number: ");
    scanf("%d", &head);

    int tracks;
    printf("Enter the total track number: ");
    scanf("%d", &tracks);

    int totalheadmoment = 0;

    printf("%d ", head);

    for (int i = 0; i < n; i++)
    {

        int diff = abs(head - disc_req[i]);

        totalheadmoment += diff;
        head = disc_req[i];
        printf("-> %d  ", head);
    }
    printf("\nTotal Head Moment: %d", totalheadmoment);
}
