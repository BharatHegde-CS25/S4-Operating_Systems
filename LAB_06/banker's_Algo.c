// BANKER'S ALGORITHM

#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10], safeSeq[10];
    int work[10], count = 0, found;

    printf("================ BANKER'S ALGORITHM ================\n\n");

    printf("Enter number of processes : ");
    scanf("%d", &n);

    printf("Enter number of resources : ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d : ", i);
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("\nEnter Maximum Matrix:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d : ", i);
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix
    printf("\n\nNeed Matrix:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d : ", i);
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < m; i++)
        work[i] = avail[i];

    for(i = 0; i < n; i++)
        finish[i] = 0;

    while(count < n)
    {
        found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    printf("\nProcess P%d is executing\n", i);

                    for(k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    printf("Available Resources: ");
                    for(k = 0; k < m; k++)
                        printf("%d ", work[k]);

                    printf("\n");

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n)
    {
        printf("\n\nSYSTEM IS IN SAFE STATE\n");

        printf("\nSafe Sequence:\n");
        for(i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if(i != n - 1)
                printf(" -> ");
        }
    }
    else
    {
        printf("\n\nSYSTEM IS NOT IN SAFE STATE");
    }

    return 0;
}
