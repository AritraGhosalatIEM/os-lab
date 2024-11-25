#include<stdio.h>
#include<stdlib.h>
int main(int argc,char** argv){
	printf("Start Position: ");
	unsigned int distance=0,last,current;
	scanf("%d",&last);
	for(int i=1;i<argc;i++){
		current=atoi(argv[i]);
		distance+=abs(last-current);
		last=current;
	}
	printf("Distance travelled : %d\n",distance);
	return 0;
}
