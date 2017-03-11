#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

int moving_sum[5] = { 0 };
sem_t sum_sem;	

typedef struct{
	int num;
	int i;
}fact;

void factorial(void* fa)
{
	fact* f = (fact*)fa;
	int fval = f->num;
	printf("thread #%d, fval is %d\n",f->i,f->num);
	if(fval == 0 || fval == 1)
		fval = 1;
	else
		for(int i = f->num-1; i > 0; i--)
		{
			printf("%d\n",i);
			fval*=i;
		}
	if(f->i == 0)
	{	
		sem_wait(&sum_sem);
		moving_sum[f->i] = fval;
		sem_post(&sum_sem);
	}
	else
	{
		sem_post(&sum_sem);
		while(1)
		{
			sem_wait(&sum_sem);
			if(moving_sum[f->i-1] > 0)
			{
				moving_sum[f->i] = fval + moving_sum[f->i-1];
				sem_post(&sum_sem);
				break;
			}
			sem_post(&sum_sem);
		}
	}

}

int main(void)
{
	pthread_t *threads = malloc(5*sizeof(pthread_t));
	fact *facts = malloc(5*sizeof(fact));
	sem_init(&sum_sem, 0, 1);
	for(int i = 0; i < 5; i++)
	{
		int num;
		printf("Enter a number: ");
		scanf("%d",&num);
		facts[i].i = i;
		facts[i].num = num;	
	}
	for(int i = 0; i<5; i++)
		pthread_create(&threads[i],NULL, (void *)&factorial, (void *)&facts[i]);
	printf("joining threads\n");
	for(int i = 0; i < 5; i++)
		pthread_join(threads[i],NULL);
	for(int i = 0; i < 5; i++)
		printf("%d ", moving_sum[i]);
	printf("\n");
	return 0;
}