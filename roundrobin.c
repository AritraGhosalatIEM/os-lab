#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define QUANTUM 3
int *pid,*arrival,*burst;
unsigned short parse(char** argv){
	unsigned short processes=1;
	for(unsigned int i=0;i<strlen(argv[1]);i++)
		if(argv[1][i]==',')
			processes++;
	pid=malloc(sizeof(int)*processes);
	arrival=malloc(sizeof(int)*processes);
	burst=malloc(sizeof(int)*processes);
	char *svpid,*svarrival,*svburst;
	char *tokpid=strtok_r(argv[1],",",&svpid),*tokarrival=strtok_r(argv[2],",",&svarrival),*tokburst=strtok_r(argv[3],",",&svburst);
	for(unsigned int i=0;i<processes;i++){
		pid[i]=atoi(tokpid);
		tokpid=strtok_r(NULL,",",&svpid);
		arrival[i]=atoi(tokarrival);
		tokarrival=strtok_r(NULL,",",&svarrival);
		burst[i]=atoi(tokburst);
		tokburst=strtok_r(NULL,",",&svburst);
	}
	return processes;
}
void bubblesort(int *keyarr,int *arr2,int *arr3,unsigned short len){
	bool sorted;
	do{
		sorted=true;
		for(unsigned short i=1;i<len;i++)
			if(keyarr[i-1]>keyarr[i]){
				sorted=false;
				int t;
				t=keyarr[i];
				keyarr[i]=keyarr[i-1];
				keyarr[i-1]=t;
				t=arr2[i];
				arr2[i]=arr2[i-1];
				arr2[i-1]=t;
				t=arr3[i];
				arr3[i]=arr3[i-1];
				arr3[i-1]=t;
			}
	}while(!sorted);
}
int head,tail,max,*queue;
bool dequeued;
void init(unsigned short size){
	max=size;
	queue=(int*)malloc(sizeof(int)*size);
	head=tail=0;
	dequeued=true;
}
#define EMPTY() (dequeued && head==tail)
bool enqueue(int val){
	if(head==tail && !dequeued)
		return false;
	dequeued=false;
	queue[head]=val;
	head=(head+1)%max;
	return true;
}
int dequeue(){
	dequeued=true;
	int r=queue[tail];
	tail=(tail+1)%max;
	return r;
}
int main(int argc,char** argv){
	unsigned short processes=parse(argv);
	bubblesort(arrival,pid,burst,processes);
	init(processes);
	int exit[processes];
	memcpy(exit,arrival,sizeof(int)*processes);
	unsigned int waiting=0,turnaround=0,time=0;
	printf("0 ");
	int process,i=0;
	do{
		for(;i<processes && arrival[i]<=time;i++)//collect ready processes
			enqueue(i);
		if(EMPTY())//shift to next time
			time=arrival[i];
		else if(burst[process=dequeue()]>QUANTUM){
			waiting+=time-exit[process];
			time+=QUANTUM;
			burst[process]-=QUANTUM;
			enqueue(process);
			exit[process]=time;
			printf("-%d-",pid[process]);
		}
		else{
			waiting+=time-exit[process];
			time+=burst[process];
			turnaround+=time-arrival[process];
			printf("-%d-",pid[process]);
		}
		printf(" %d ",time);
	}while(i<processes || !EMPTY());
	printf("\nAverage turnaround time: %f\nAverage waiting time: %f\n",(double)turnaround/processes,(double)waiting/processes);
	return 0;
}
