#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int total_sum = 0;
sem_t sem;

void *factorial(void *t);
int fac(int number);

int main(void){
	pid_t pid;
	pthread_t tid[5];
	FILE *num_file_write, *num_file_read, *sum_file;
	int num;
	int error;

	num_file_write = fopen("numbers.txt", "w");

	printf("Please enter 5 numbers:\n");
	for(int i = 0; i < 5; i++){
		scanf("%d", &num);
		fprintf(num_file_write, "%d\n", num);
	}
	fclose(num_file_write);
	pid = fork();
	if(pid < 0){
		return 1;
	}else if(pid == 0){
		sem_init(&sem, 0, 1);
		num_file_read = fopen("numbers.txt", "r");
		for(int i = 0; i < 5; i++){
			fscanf(num_file_read, "%d", &num);
			error = pthread_create(&tid[i], NULL, factorial, (void*)num);
			if(error){
				printf("ERROR: create() thread %d\n", error);
				exit(-1);
			}
		}
		fclose(num_file_read);

		for(int i = 0; i < 5; i++){
			error = pthread_join(tid[i], NULL);
			if(error){
				printf("ERROR: join() thread %d\n", error);
				exit(-1);
			}
		}

		sem_destroy(&sem);

		sum_file = fopen("sum.txt", "w");
		fprintf(sum_file, "%d\n", total_sum);
		fclose(sum_file);
	} else {
		wait(NULL);
	}
}

void *factorial(void *t){
	int sum = 0;
	int data = (int)t; 
	sum = fac(data);
	sem_wait(&sem);
	total_sum += sum;
	sem_post(&sem);
	pthread_exit(NULL);
}

int fac(int number){
	if(number == 1 || number == 0){
		return 1;
	}else{
		return number * fac(number - 1);
	}
}