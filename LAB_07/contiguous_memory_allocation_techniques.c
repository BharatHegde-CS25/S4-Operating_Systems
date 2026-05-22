// CONTIGUOUS MEMORY ALLOCATION
// First Fit, Best Fit and Worst Fit

#include <stdio.h>

void firstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[10];
    int temp[10];
    int i, j;

    for(i = 0; i < blocks; i++)
        temp[i] = blockSize[i];

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        for(j = 0; j < blocks; j++)
        {
            if(temp[j] >= processSize[i])
            {
                allocation[i] = j;
                temp[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n\n");
    printf("Process No.  Process Size     Block No.\n");

    for(i = 0; i < processes; i++)
    {
        printf("%d\t     %d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[10];
    int temp[10];
    int i, j, bestIdx;

    for(i = 0; i < blocks; i++)
        temp[i] = blockSize[i];

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        bestIdx = -1;

        for(j = 0; j < blocks; j++)
        {
            if(temp[j] >= processSize[i])
            {
                if(bestIdx == -1 || temp[j] < temp[bestIdx])
                    bestIdx = j;
            }
        }

        if(bestIdx != -1)
        {
            allocation[i] = bestIdx;
            temp[bestIdx] -= processSize[i];
        }
    }

    printf("\n\n--- Best Fit ---\n\n");
    printf("Process No.  Process Size     Block No.\n");

    for(i = 0; i < processes; i++)
    {
        printf("%d\t     %d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[10];
    int temp[10];
    int i, j, worstIdx;

    for(i = 0; i < blocks; i++)
        temp[i] = blockSize[i];

    for(i = 0; i < processes; i++)
        allocation[i] = -1;

    for(i = 0; i < processes; i++)
    {
        worstIdx = -1;

        for(j = 0; j < blocks; j++)
        {
            if(temp[j] >= processSize[i])
            {
                if(worstIdx == -1 || temp[j] > temp[worstIdx])
                    worstIdx = j;
            }
        }

        if(worstIdx != -1)
        {
            allocation[i] = worstIdx;
            temp[worstIdx] -= processSize[i];
        }
    }

    printf("\n\n--- Worst Fit ---\n\n");
    printf("Process No.  Process Size     Block No.\n");

    for(i = 0; i < processes; i++)
    {
        printf("%d\t     %d\t\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int blockSize[10], processSize[10];
    int blocks, processes;
    int i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);

    printf("\nEnter sizes of %d memory blocks:\n", blocks);

    for(i = 0; i < blocks; i++)
        scanf("%d", &blockSize[i]);

    printf("\nEnter number of processes: ");
    scanf("%d", &processes);

    printf("\nEnter sizes of %d processes:\n", processes);

    for(i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    firstFit(blockSize, blocks, processSize, processes);

    bestFit(blockSize, blocks, processSize, processes);

    worstFit(blockSize, blocks, processSize, processes);

    return 0;
}
