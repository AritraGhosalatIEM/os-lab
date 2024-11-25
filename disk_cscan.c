#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char** argv){
	printf("Start Position: ");
	unsigned int last;
	scanf("%d",&last);
	unsigned int min,max,t;
	int final=-1;
	max=min=atoi(argv[1]);
		for(int i=2;i<argc;i++){
		t=atoi(argv[i]);
		if(t<min)min=t;
		if(t>max)max=t;
		if(t>final && t<last)final=t;
	}
	printf("%d %d %d",max,last,final);
	printf("Distance travelled : %d\n",abs(max-last)+max+final);
	return 0;
}
