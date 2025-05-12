#include<stdio.h>

int findLRU(int time[], int nf)
{
    int min=time[0];
    int pos=0;

    for(int i=1; i<nf; i++)
    {
        if(time[i]<min)
        {
            min=time[i];
            pos=i;
        }
    }
    return pos;
}

int main()
{
    int np; //number of pages
    int nf; //number of frames
    printf("Enter number of pages:\n");
    scanf("%d", &np);

    printf("Enter number of frames:\n");
    scanf("%d", &nf);

    int p[np], f[nf], time[nf], pageFaults=0, count=0, pos, hit;
    printf("Enter page reference string:\n");
    for(int i=0; i<np; i++)
    {
        scanf("%d", &p[i]);
    }

    for(int i=0; i<nf; i++)
    {
        f[i]=-1;
        time[i]=0;
    }

    for(int i=0; i<np; i++)
    {
        hit=0;
        for(int j=0; j<nf; j++)
        {
            //for hit
            if(f[j]==p[i])
            {
                count++;
                time[j]=count;
                hit=1;
                break;
            }
        }

        if(hit==0) //miss
        {
            pos=-1;
            for(int j=0; j<nf; j++)
            {
                if(f[j]==-1) //there still is some empty space in frame
                {
                    pos=j;
                    break;
                }
            }

            if(pos==-1)//there is no empty space in frame
            {
                pos=findLRU(time, nf);
            }
            f[pos]=p[i];
            count++;
            time[pos]=count;
            pageFaults++;
        }

        printf("Frames after page %d\n", p[i]);
        for(int j=0; j<nf; j++)
        {
            if(f[j] != -1)
            {
                printf("%d ", f[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total page hit = %d\n", np-pageFaults);
    printf("Total page faults = %d\n", pageFaults);
    
}
