#include<pthread.h>
#include<stdio.h>
#define PRODUCE() resource++;printf("Resource produced\n")
#define CONSUME() resource--;printf("Resource consumed\n")
int resource;
unsigned int full;
unsigned int empty;
void wait(unsigned int *s){
	while(*s==0);
	*s--;
}
void signal(unsigned int *s){
	*s++;
}
void *producer(void *arg){
	for(;;){
		wait(&empty);
		PRODUCE();
		signal(&full);
	}
}
void *consumer(void *arg){
	for(;;){
		wait(&empty);
		CONSUME();
		signal(&empty);
	}
}
int main(){
	resource=0;
	full=0;
	empty=1;
	pthread_t consumer_thread;
	pthread_create(&consumer_thread,NULL,consumer,NULL);
	pthread_t producer_thread;
	pthread_create(&producer_thread,NULL,producer,NULL);
	pthread_join(producer_thread,NULL);
	pthread_join(consumer_thread,NULL);
}
