#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main() {
    // Define data
    int n, disc_req[200], head, tracks, pending, diff, min, index, finish[200], total_head_movement = 0;

    // Accept data
    printf("Enter number of disc requests, initial head position, and number of tracks:\n");
    scanf("%d %d %d", &n, &head, &tracks);
   
    printf("Enter the disc requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &disc_req[i]);
        finish[i] = 0;
    }

    pending = n;

    printf("%d", head);

    while (pending > 0) {
        min = 1000;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                diff = abs(head - disc_req[i]);
                if (diff < min) {
                    min = diff;
                    index = i;
                }
            }
        }

        total_head_movement += min;
        head = disc_req[index];
        finish[index] = 1;
        pending--;

        printf(" -> %d", head);
    }

    printf("\nTotal head movements: %d\n", total_head_movement);
    return 0;
}
