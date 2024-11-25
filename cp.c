/*
	WAP in C to simulate cp command
		Start the program
		Declare the variables ch, *fp, sc=0;
		Open the file in read mode
		Get characters
		if ch== " " sc values by one
		print the no of files
		close
*/
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char** argv){
	char ch;FILE* fp;
	FILE* from=fopen(argv[1],"r");
	fp=fopen(argv[2],"w");
	char* buf[1];
	while(fread(buf,1,1,from))
		fprintf(fp,"%s",buf);
	fclose(fp);fclose(from);
	printf("one file copied\n");
	return 0;
}
