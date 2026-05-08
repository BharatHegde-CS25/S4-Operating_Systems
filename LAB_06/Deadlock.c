// DEADLOCK DETECTION ALGORITHM

#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[10][10], request[10][10];
    int avail[10], work[10];
    int finish[10];
    int found;

    printf("================ DEADLOCK DETECTION ================\n\n");

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

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d : ", i);
        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);
    }

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for(i = 0; i < m; i++)
        work[i] = avail[i];

    for(i = 0; i < n; i++)
    {
        int allocated = 0;

        for(j = 0; j < m; j++)
        {
            if(alloc[i][j] != 0)
            {
                allocated = 1;
                break;
            }
        }

        if(allocated)
            finish[i] = 0;
        else
            finish[i] = 1;
    }

    while(1)
    {
        found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    printf("\nProcess P%d can finish\n", i);

                    for(k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    printf("Available Resources: ");
                    for(k = 0; k < m; k++)
                        printf("%d ", work[k]);

                    printf("\n");

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    int deadlock = 0;

    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            deadlock = 1;
            break;
        }
    }

    if(deadlock)
    {
        printf("\n\nDEADLOCK DETECTED\n");

        printf("\nProcesses in deadlock:\n");

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
                printf("P%d ", i);
        }
    }
    else
    {
        printf("\n\nNO DEADLOCK DETECTED");
        printf("\nAll processes can finish successfully.");
    }

    return 0;
}
