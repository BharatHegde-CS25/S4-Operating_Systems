#include <stdio.h>

int main()
{
    int n,i,j,choice;
    int at[20], bt[20], ct[20], wt[20], tat[20];
    int rt[20], completed = 0, time = 0;
    int min, shortest;
    int finish;
    float avg_wt=0, avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d Arrival Time: ",i+1);
        scanf("%d",&at[i]);

        printf("Process %d Burst Time: ",i+1);
        scanf("%d",&bt[i]);

        rt[i] = bt[i];   // remaining time for preemptive
    }

    printf("\n1. SJF Non-Preemptive\n2. SJF Preemptive\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    if(choice==1)
    {
        // SJF NON PREEMPTIVE
        int p[20];

        for(i=0;i<n;i++)
            p[i]=i;

        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(bt[p[i]] > bt[p[j]])
                {
                    int temp=p[i];
                    p[i]=p[j];
                    p[j]=temp;
                }
            }
        }

        int current_time=0;

        for(i=0;i<n;i++)
        {
            if(current_time < at[p[i]])
                current_time = at[p[i]];

            ct[p[i]] = current_time + bt[p[i]];
            current_time = ct[p[i]];

            tat[p[i]] = ct[p[i]] - at[p[i]];
            wt[p[i]] = tat[p[i]] - bt[p[i]];

            avg_tat += tat[p[i]];
            avg_wt += wt[p[i]];
        }
    }
    else
    {
        // SJF PREEMPTIVE (SRTF)

        while(completed != n)
        {
            min = 9999;
            shortest = -1;

            for(i=0;i<n;i++)
            {
                if(at[i] <= time && rt[i] < min && rt[i] > 0)
                {
                    min = rt[i];
                    shortest = i;
                }
            }

            if(shortest == -1)
            {
                time++;
                continue;
            }

            rt[shortest]--;

            if(rt[shortest] == 0)
            {
                completed++;
                finish = time + 1;

                ct[shortest] = finish;
                tat[shortest] = ct[shortest] - at[shortest];
                wt[shortest] = tat[shortest] - bt[shortest];

                avg_tat += tat[shortest];
                avg_wt += wt[shortest];
            }

            time++;
        }
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f",avg_tat/n);
    printf("\nAverage Waiting Time = %.2f",avg_wt/n);

    return 0;
}
