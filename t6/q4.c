#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUMBERS 10

int buffer[5] = { 0 };

sem_t sem;	

void producer(void* n)
{
	int *nums = (int*)n;
	int i = 0;
	int full = -1;
	while(i < 10)
	{
		srand(time(NULL));
		sleep(rand()%3);
		sem_wait(&sem);
		for(int j = 0; j < 5; j++)
		{
			if(buffer[j] == 0)
			{
				full = j;
				break;
			}
		}
		if(full != -1)
		{
			buffer[full] = nums[i];
			printf("Produced %d\n", nums[i]);
			sem_post(&sem);
			i++;
		}
		else
			sem_post(&sem);
	}
}

void consumer()
{
	int i = 0;
	int empty = -1;
	while(i < 10)
	{
		srand(time(NULL));
		sleep(rand()%3);
		sem_wait(&sem);
		for(int j = 0; j < 5; j++)
		{
			if(buffer[j] != 0)
			{
				empty = j;
				break;
			}
		}
		if(empty != -1)
		{
			printf("Consumed %d\n", buffer[empty]);
			buffer[empty] = 0;
			sem_post(&sem);
			i++;
			empty = 1;
		}
		else
			sem_post(&sem);
	}
}

int main(void)
{
	pthread_t prod;
	pthread_t cons;
	int nums[NUMBERS];
	sem_init(&sem, 0, 1);
	for(int i = 0; i < NUMBERS; i++)
	{
		printf("Enter a number: ");
		scanf("%d",&nums[i]);
	}
	pthread_create(&prod,NULL,(void*)&producer,(void*)nums);
	pthread_create(&cons, NULL, (void*)&consumer,NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	printf("Buffer: ");
	for(int i = 0; i < 5; i++)
		printf("%d ",buffer[i]);
	printf("\n");

	return 0;
}