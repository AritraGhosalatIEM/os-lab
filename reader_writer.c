#include<time.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
#define READERS 5
#define WRITERS 2
unsigned int readcount,write;
void wait(unsigned int *s){
	while(*s==0);
	*s--;
}
void signal(unsigned int *s){
	*s++;
}
void* reader(void* arg){
	for(;;){
		readcount++;
		if(readcount==1)
			wait(&write);
		FILE* fp=fopen("an_file.txt","r");
		fseek(fp,0L,SEEK_END);
		int size=ftell(fp);
		rewind(fp);
		char *buff=malloc(size);
		printf("Content of file: ");
		fread(buff,1,size,fp);
		fwrite(buff,1,size,stdout);
		free(buff);
		printf("\n");
		fclose(fp);
		readcount--;
		if(readcount==0)
			signal(&write);
	}
}
void* writer(void* arg){
	for(;;){
		wait(&write);
		FILE* fp=fopen("an_file.txt","a");
		int c=rand()%26+65;
		fwrite(&c,1,1,fp);
		printf("Writtern %c to file.\n",c);
		fclose(fp);
		signal(&write);
	}
}
int main(){
	srand(time(NULL));
	readcount=0;
	write=1;
	pthread_t readers[READERS],writers[WRITERS];
	for(int i=0;i<READERS;i++)pthread_create(&readers[i],NULL,reader,NULL);
	for(int i=0;i<WRITERS;i++)pthread_create(&writers[i],NULL,writer,NULL);
	for(int i=0;i<READERS;i++)pthread_join(readers[i],NULL);
	for(int i=0;i<WRITERS;i++)pthread_join(writers[i],NULL);
	return 0;
}
