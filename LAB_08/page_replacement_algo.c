// PAGE REPLACEMENT ALGORITHMS
// FIFO, LRU and OPTIMAL

#include <stdio.h>

int search(int key, int frame[], int f)
{
    int i;

    for(i = 0; i < f; i++)
    {
        if(frame[i] == key)
            return 1;
    }

    return 0;
}

// ---------------- FIFO ----------------

void fifo(int pages[], int n, int f)
{
    int frame[10], i, j;
    int index = 0, faults = 0;

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\n--- FIFO PAGE REPLACEMENT ---\n");

    for(i = 0; i < n; i++)
    {
        if(search(pages[i], frame, f))
        {
            printf("\n%d -> ", pages[i]);

            for(j = 0; j < f; j++)
                printf("%d ", frame[j]);

            printf("(Hit)");
        }
        else
        {
            frame[index] = pages[i];
            index = (index + 1) % f;
            faults++;

            printf("\n%d -> ", pages[i]);

            for(j = 0; j < f; j++)
                printf("%d ", frame[j]);

            printf("(Fault)");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

// ---------------- LRU ----------------

void lru(int pages[], int n, int f)
{
    int frame[10], time[10];
    int i, j, pos, faults = 0, counter = 0;

    for(i = 0; i < f; i++)
    {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\n\n--- LRU PAGE REPLACEMENT ---\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < f; j++)
        {
            if(frame[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(found)
        {
            printf("\n%d -> ", pages[i]);

            for(j = 0; j < f; j++)
                printf("%d ", frame[j]);

            printf("(Hit)");
        }
        else
        {
            pos = 0;

            for(j = 1; j < f; j++)
            {
                if(time[j] < time[pos])
                    pos = j;
            }

            counter++;
            frame[pos] = pages[i];
            time[pos] = counter;
            faults++;

            printf("\n%d -> ", pages[i]);

            for(j = 0; j < f; j++)
                printf("%d ", frame[j]);

            printf("(Fault)");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

// ---------------- OPTIMAL ----------------

void optimal(int pages[], int n, int f)
{
    int frame[10];
    int i, j, k, pos, faults = 0;

    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\n\n--- OPTIMAL PAGE REPLACEMENT ---\n");

    for(i = 0; i < n; i++)
    {
        if(search(pages[i], frame, f))
        {
            printf("\n%d -> ", pages[i]);

            for(j = 0; j < f; j++)
                printf("%d ", frame[j]);

            printf("(Hit)");
        }
        else
        {
            int farthest = -1;
            pos = -1;

            for(j = 0; j < f; j++)
            {
                int found = 0;

                for(k = i + 1; k < n; k++)
                {
                    if(frame[j] == pages[k])
                    {
                        found = 1;

                        if(k > farthest)
                        {
                            farthest = k;
                            pos = j;
                        }

                        break;
                    }
                }

                if(!found)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
                pos = 0;

            frame[pos] = pages[i];
            faults++;

            printf("\n%d -> ", pages[i]);

            for(j = 0; j < f; j++)
                printf("%d ", frame[j]);

            printf("(Fault)");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

// ---------------- MAIN ----------------

int main()
{
    int pages[50];
    int n, f, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(pages, n, f);

    lru(pages, n, f);

    optimal(pages, n, f);

    return 0;
}
