#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include<malloc.h>
#define TOTAL 5
unsigned int *chopstick;
bool *eating;
void wait(unsigned int *s){
	while(*s==0);
	*s--;
}
void signal(unsigned int *s){
	*s++;
}
void eat(int id){
	if(!eating[id]){
		printf("Philosopher %d is eating.\n",id);
		eating[id]=true;
	}
}
void think(int id){
	if(eating[id]){
		printf("Philosopher %d is thinking.\n",id);
		eating[id]=false;
	}
}
void *philosopher(void* number){
	int id=*(int*)number;
	for(;;){
		wait(&chopstick[id]);wait(&chopstick[(id+1)%TOTAL]);
		eat(id);
		signal(&chopstick[id]);signal(&chopstick[(id+1)%TOTAL]);
		think(id);
	}
}
int main(){
	chopstick=(int*)malloc(sizeof(int)*TOTAL);
	eating=(bool*)malloc(sizeof(int)*TOTAL);
	unsigned int args[TOTAL];
	for(unsigned int i=0;i<TOTAL;i++){
		chopstick[i]=1;
		eating[i]=false;
		args[i]=i;
	}
	pthread_t philosophers[TOTAL];
	for(int i=0;i<TOTAL;i++)pthread_create(&philosophers[i],NULL,philosopher,&args[i]);
	for(int i=0;i<TOTAL;i++)pthread_join(philosophers[i],NULL);
	return 0;
}
