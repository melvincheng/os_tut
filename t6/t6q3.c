#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int moving_sum[5] = { 0 };
sem_t sem;

typedef struct{
	int number;
	int index;
} num;

void * factorial(void * arg);
int fac(int number);

int main(void){
	pthread_t tid[5];
	num nums[5];

	sem_init(&sem, 0, 1);

	printf("Please enter 5 numbers:\n");
	for(int i = 0; i < 5; i++){
		nums[i].index = i;
		fscanf(stdin, "%d", &nums[i].number);
	}

	printf("Running... \n");
	for(int i = 0; i < 5; i++){
		pthread_create(&tid[i], NULL, factorial, (void *)&nums[i]);
	}

	for(int i = 0; i < 5; i++){
		pthread_join(tid[i], NULL);
	}

	sem_destroy(&sem);
	
}

void * factorial(void * arg){
	int number;
	num * temp_num = (num*)arg;
	number = fac(temp_num->number);
	while(1){
		sem_wait(&sem);
		if(moving_sum[temp_num->index] > 0){
			printf("%d\n", temp_num->number);
			number += moving_sum[temp_num->index-1];
			moving_sum[temp_num->index] += number;
			pthread_exit(0);
		}
		sem_post(&sem);
	}

}

int fac(int number){
	if(number == 1 || number == 0){
		return 1;
	}else{
		return number * fac(number - 1);
	}
}