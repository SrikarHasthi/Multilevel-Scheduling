#include<stdio.h>
struct process
{
    int pro_Id;
    int arrT,burT,waiturnT,turnT,priority,burTcopy;
}queue1[10],queue2[10];
void main()
{
	struct process temp;
    int i,time=0,t1,t2,bu_t=0,largest,totalProcess,count=0,k,p=0,totalProcess2,n,pos,j,flag=0,y;
    float wait_time=0,turnaround_time= 0,average_waiting_time,average_turnaround_time;
    printf("\nEnter Number of Processes :   ");
    scanf("%d",&totalProcess);
    n=totalProcess;
    for(i=0;i<totalProcess;i++)
    {
    	printf("\nProcess %d",i+1);
    	printf("\nEnter Process Id: ");
    	//fflush(stdin);
        scanf("%d",&queue1[i].pro_Id);
        printf("\nEnter Details For processor %d:\n",queue1[i].pro_Id);
        printf("Enter Arrival Time: ");
        scanf("%d",&queue1[i].arrT);
        printf("Enter Burst Time: ");
        scanf("%d",&queue1[i].burT);
        queue1[i].burTcopy=queue1[i].burT;
        printf("Enter Priority:  ");
        scanf("%d",&queue1[i].priority);
    }
    printf("\nEnter Time Quantum for Fixed priority queue: ");
    scanf("%d",&t1);
    printf("\nEnter Time Quantum for Round Robin queue: ");
    scanf("%d",&t2);
    printf("\n--------------------------------------\n");
    printf("Process\t|Turnaround Time|Waiting Time|\n");
    printf("--------------------------------------\n");
    for(i=0;i<totalProcess;i++)
    {
        pos=i;
        for(j=i+1;j<totalProcess;j++)
        {
            if(queue1[j].arrT<queue1[pos].arrT)
                pos=j;
        }
        temp=queue1[i];
        queue1[i]=queue1[pos];
        queue1[pos]=temp;
    }
    time=queue1[0].arrT;
    for(i=0;totalProcess!=0;i++)
    {
    	while(count!=t1)
    	{
    		count++;
    		if(queue1[i].arrT<=time)
    		{
    			for(j=i+1;j<totalProcess;j++)
    			{
    				if(queue1[j].arrT==time&&queue1[j].priority<queue1[i].priority)
    				{
    					queue2[p]=queue1[i];
						p++;
    					for(k=i;k<totalProcess-1;k++)
    						queue1[k]=queue1[k+1];
    					totalProcess--;
						count=0;
    					i=j-1;
    					j--;
					}
				}
			}
			time++;
			queue1[i].burT--;
			if(queue1[i].burT==0)
			{
				queue1[i].turnT=time-queue1[i].arrT;
				queue1[i].waiturnT=queue1[i].turnT-queue1[i].burTcopy;
				printf("%d\t|\t%d\t|\t%d    |\n",queue1[i].pro_Id,queue1[i].turnT,queue1[i].waiturnT);
				printf("--------------------------------------\n");
				wait_time+=time-queue1[i].arrT-queue1[i].burTcopy; 
    			turnaround_time+=time-queue1[i].arrT;
    			for(k=i;k<totalProcess-1;k++)
    				queue1[k]=queue1[k+1];i--;
    			totalProcess--;
				count=t1;break;
			}
		}
		count=0;
		if(queue1[i].burT!=0)
		{
			queue2[p]=queue1[i];
			p++;
			for(k=i;k<totalProcess-1;k++)
    			queue1[k]=queue1[k+1];
    		totalProcess--;
		}
			if(i==totalProcess-1)
				i=-1;
	}
	
	totalProcess2=p;
	for(count=0;totalProcess2!=0;) 
	{ 
		if(queue2[count].burT<=t2&&queue2[count].burT>0) 
    	{ 
    		time+=queue2[count].burT; 
    		queue2[count].burT=0; 
    		flag=1; 
    	} 
    	else if(queue2[count].burT>0) 
    	{ 
    		queue2[count].burT-=t2; 
    		time+=t2; 
    	} 
    	if(queue2[count].burT==0&&flag==1) 
    	{ 
    		totalProcess2--; 
    		queue2[count].turnT=time-queue2[count].arrT;
			queue2[count].waiturnT=queue2[count].turnT-queue2[count].burTcopy; 
			printf("%d\t|\t%d\t|\t%d\n",queue2[count].pro_Id,queue2[count].turnT,queue2[count].waiturnT); 
    		turnaround_time+=time-queue2[count].arrT;
    		wait_time+=time-queue2[count].arrT-queue2[count].burTcopy;
    		for(k=count;k<totalProcess2;k++)
    			queue2[k]=queue2[k+1];count--;
    		flag=0; 
    	} 

    	if(count==totalProcess2-1) 
      		count=0; 
    	else 
    		count++; 
    }
    printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
    printf("Avg Turnaround Time = %f",turnaround_time*1.0/n);   
}
