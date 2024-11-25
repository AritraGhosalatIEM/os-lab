#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int *pid,*arrival,*burst,*priority;
unsigned short parse(char** argv){
	unsigned short processes=1;
	for(unsigned int i=0;i<strlen(argv[1]);i++)
		if(argv[1][i]==',')
			processes++;
	pid=malloc(sizeof(int)*processes);
	arrival=malloc(sizeof(int)*processes);
	burst=malloc(sizeof(int)*processes);
	priority=malloc(sizeof(int)*processes);
	char *svpid,*svarrival,*svburst,*svpriority;
	char *tokpid=strtok_r(argv[1],",",&svpid),*tokarrival=strtok_r(argv[2],",",&svarrival),*tokburst=strtok_r(argv[3],",",&svburst),*tokpriority=strtok_r(argv[4],",",&svpriority);
	for(unsigned int i=0;i<processes;i++){
		pid[i]=atoi(tokpid);
		tokpid=strtok_r(NULL,",",&svpid);
		arrival[i]=atoi(tokarrival);
		tokarrival=strtok_r(NULL,",",&svarrival);
		burst[i]=atoi(tokburst);
		tokburst=strtok_r(NULL,",",&svburst);
		priority[i]=atoi(tokpriority);
		tokpriority=strtok_r(NULL,",",&svpriority);
	}
	return processes;
}
void bubblesort(int *keyarr,int *key2,int *arr2,int *arr3,unsigned short len){
	bool sorted;
	do{
		sorted=true;
		for(unsigned short i=1;i<len;i++)
			if(keyarr[i-1]>keyarr[i] || (keyarr[i-1]==keyarr[i] && key2[i-1]>key2[i])){
				sorted=false;
				int t;
				t=keyarr[i];
				keyarr[i]=keyarr[i-1];
				keyarr[i-1]=t;
				t=key2[i];
				key2[i]=key2[i-1];
				key2[i-1]=t;
				t=arr2[i];
				arr2[i]=arr2[i-1];
				arr2[i-1]=t;
				t=arr3[i];
				arr3[i]=arr3[i-1];
				arr3[i-1]=t;
			}
	}while(!sorted);
}
int main(int argc,char** argv){
	unsigned short processes=parse(argv);
	bubblesort(arrival,priority,pid,burst,processes);
	unsigned int waiting=0,turnaround=0,time=0,arrived;
	printf("0 ");
	for(unsigned short i=0;i<processes;i++){
		if(time<arrival[i])
			printf(" %d ",time=arrival[i]);
		waiting+=(time-arrival[i]);
		printf("-%d-",pid[i]);
		turnaround+=(time+=burst[i])-arrival[i];
		printf(" %d ",time);
		for(arrived=1;(i+arrived)<processes && arrival[i+arrived]<=time;arrived++);
		bubblesort(priority+i+1,arrival+i+1,pid+i+1,burst+i+1,arrived-1);
	}
	printf("\nAverage turnaround time: %f\nAverage waiting time: %f\n",(double)turnaround/processes,(double)waiting/processes);
	return 0;
}
