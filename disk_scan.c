#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char** argv){
	printf("Start Position: ");
	unsigned int last;
	scanf("%d",&last);
	unsigned int min,max,t;
	max=min=atoi(argv[1]);
	for(int i=2;i<argc;i++){
		t=atoi(argv[i]);
		if(t<min)min=t;
		if(t>max)max=t;
	}
	
	printf("Distance travelled : %d\n",abs(max-last)+max-min);
	return 0;
}
