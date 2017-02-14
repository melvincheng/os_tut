#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *bellcurve(void *grade)
{
	int g = (int)grade;
	printf("Bellcurve: %f\n", g*1.5f);
	pthread_exit(NULL);
}

int main(void)
{
	int *grades = malloc(5*sizeof(int));
	for(int i = 0; i < 5; i++)
	{
		printf("Enter grade: ");
		scanf("%d",&grades[i]);
	}
	pthread_t *pts = malloc(5*sizeof(pthread_t));
	for(int i = 0; i < 5; i++)
	{
		pthread_create(&pts[i],NULL,bellcurve,(void*)grades[i]);
	}

	pthread_exit(NULL);
}