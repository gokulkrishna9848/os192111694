#include<stdio.h>
int main()
{
	int n,b[20],wt[20],tat[20],i,j,p[20],pos,temp,pr[20];
	float A_wt,A_tat;
	printf("enter the no of processes=");
	scanf("%d",&n);
	printf("enter the burst time and priority\n");
	for(i=0;i<n;i++)
	{
		printf("\np%d\n",i+1);
		printf("burst time:");
		scanf("%d",&b[i]);
		printf("priority:");
		scanf("%d",&pr[i]);
		p[i]=i+1;
	}
	for(i=0;i<n;i++)
	{
		pos=i;
		for(j=i+1;j<n;j++)
		if(pr[j]<pr[pos])
		pos=j;
		temp=pr[i];
		pr[i]=pr[pos];
		pr[pos]=temp;
		temp=b[i];
		b[i]=b[pos];
		b[pos]=temp;
		temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
	}
	wt[0]=0;
	for(i=1;i<n;i++)
	{
		wt[i]=0;
		for(j=0;j<i;j++)
		wt[i]+=b[j];
		A_wt+=wt[i];
	}
	A_wt/=n;
	printf("process   burst_time   waiting_time  turnaround_time\n");
	for(i=0;i<n;i++)
	{
		tat[i]=wt[i]+b[i];
		A_tat+=tat[i];
		printf("p[%d]   %d    %d   %d\n",i+1,b[i],wt[i],tat[i]);
	}
	A_tat/=n;
	printf("AVERAGE WAITING TIME = %f\n",A_wt);
	printf("AVERAGE TAT = %f",A_tat);
}