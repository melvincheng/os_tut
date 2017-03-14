#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int total_sum;
sem_t sem;

void factorial(void* n)
{
	int num = (int)n;
	int count = num;
	int fval = count;
	printf("Calculating %d!\n", count);
	if(count == 0 || count == 1)
		printf("Total factorial value: 1\n");
	else
	{
		while(count > 0)
		{
			printf("Current factorial value: %d\n",fval);
			fval*= count;
			count--;
		}
		printf("Total factorial value: %d\n", fval);
	}
	sem_wait(&sem);
	total_sum+=fval;
	sem_post(&sem);
}

int main(void)
{
	sem_init(&sem,0,1);
	pid_t pid;
	int status = 0;
	int n;
	FILE* f = fopen("numbers.txt","w");
	for(int i = 0; i < 5; i++)
	{
		printf("Enter a number: ");
		scanf("%d",&n);
		fprintf(f,"%d\n",n);
	}
	fclose(f);
	pid = fork();
	if(!pid)
	{
		pthread_t *threads = malloc(5*sizeof(pthread_t));
		f = fopen("numbers.txt", "r");
		for(int i = 0; i < 5; i++)
		{
			int n;
			fscanf(f,"%d", &n);
			pthread_create(&threads[i],NULL,(void*)factorial,(void*)n);
		}
		fclose(f);
		for(int i = 0; i < 5; i++)
			pthread_join(threads[i],NULL);
		f = fopen("sum.txt", "w");
		fprintf(f,"%d",total_sum);
		fclose(f);
	}
	else
	{
		while((pid = wait(&status)) > 0);
		f = fopen("sum.txt","r");
		int sum;
		fscanf(f,"%d",&sum);
		fclose(f);
		printf("Total sum is %d\n",sum);
	}
	return 0;
}