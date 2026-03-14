#include<stdio.h>

int main()
{
    int n,i,j,choice;
    int p[20], at[20], bt[20], pr[20];
    int ct[20], tat[20], wt[20];
    int rt[20];
    int time=0, completed=0, min_pr, index;
    float avg_tat=0, avg_wt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        p[i] = i+1;

        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        printf("Priority: ");
        scanf("%d",&pr[i]);

        rt[i] = bt[i];
    }

    printf("\n1. Non Preemptive Priority");
    printf("\n2. Preemptive Priority");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);

    // -------- NON PREEMPTIVE --------
    if(choice==1)
    {
        int temp;

        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(pr[i] > pr[j])
                {
                    temp=pr[i]; pr[i]=pr[j]; pr[j]=temp;
                    temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
                    temp=at[i]; at[i]=at[j]; at[j]=temp;
                    temp=p[i];  p[i]=p[j];  p[j]=temp;
                }
            }
        }

        ct[0] = at[0] + bt[0];

        for(i=1;i<n;i++)
            ct[i] = ct[i-1] + bt[i];

        for(i=0;i<n;i++)
        {
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
        }
    }

    // -------- PREEMPTIVE --------
    else if(choice==2)
    {
        int done[20]={0};

        while(completed<n)
        {
            min_pr = 9999;
            index = -1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && done[i]==0)
                {
                    if(pr[i] < min_pr)
                    {
                        min_pr = pr[i];
                        index = i;
                    }
                }
            }

            if(index!=-1)
            {
                rt[index]--;
                time++;

                if(rt[index]==0)
                {
                    ct[index] = time;
                    done[index]=1;
                    completed++;

                    tat[index] = ct[index] - at[index];
                    wt[index] = tat[index] - bt[index];
                }
            }
            else
                time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat = avg_tat / n;
    avg_wt = avg_wt / n;

    printf("\nAverage Turnaround Time = %.2f",avg_tat);
    printf("\nAverage Waiting Time = %.2f",avg_wt);

    return 0;
}
