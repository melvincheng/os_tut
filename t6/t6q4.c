#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMBERS	10

sem_t buffer_access;

int buffer[5] = { 0 };
int nums[NUMBERS];
void *producer(void *t);
void *consumer(void *t);
int produce(int i);
int consume();
int main(void){
	pthread_t tid[2];

	sem_init(&buffer_access, 0, 1);

	printf("Please enter 10 numbers:\n");
	for(int i = 0; i < 10; i++){
		scanf("%d", &nums[i]);
	}

	printf("Running...\n");
	pthread_create(&tid[0], NULL, producer, NULL);
	pthread_create(&tid[1], NULL, consumer, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	for(int i = 0; i < 5; i++){
		printf("%d\n", buffer[i]);
	}
	sem_destroy(&buffer_access);
	pthread_exit(NULL);
}

void *producer(void *t){
	int swap = 1;
	for(int i = 0; i < NUMBERS; i++){
		sleep(rand()%3);
		while(1){
			sem_wait(&buffer_access);
			swap = produce(i);
			sem_post(&buffer_access);
			if(swap == 0){
				break;
			}
		}
	}
	pthread_exit(NULL);
}

int produce(int i){
	for(int j = 0; j < 5; j++){
		if(buffer[j] == 0){
			printf("Produced %d\n", nums[i]);
			buffer[j] = nums[i];
			return 0;
		}
	}
	return 1;
}

void *consumer(void *t){
	int swap = 1;
	for(int i = 0; i < NUMBERS; i++){
		sleep(rand()%3);
		while(1){
			sem_wait(&buffer_access);
			swap = consume();
			sem_post(&buffer_access);
			if(swap == 0){
				break;
			}
		}
	}
	pthread_exit(NULL);
}

int consume(){
	for(int j = 0; j < 5; j++){
		if(buffer[j] != 0){
			printf("Consumed %d\n", buffer[j]);
			buffer[j] = 0;	
			return 0;
		}
	}
	return 1;
}