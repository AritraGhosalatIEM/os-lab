#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1024
int main(int argc,char** argv){
	char* buf[strlen(argv[1])];
	char* linebuf=(char*)calloc(1,MAX);
	FILE* fp=fopen(argv[2],"r");
	fscanf(fp,"%[^\n]s",linebuf);
	printf("line : %s \n",linebuf);
	fclose(fp);
	return 0;
}
