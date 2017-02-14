#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int total_grade = 0;
pthread_mutex_t grade_mutex;

void *class_total(void *grade)
{

	int g = (int)grade;
	pthread_mutex_lock(&grade_mutex);
	total_grade+=g;
	pthread_mutex_unlock(&grade_mutex);
	pthread_exit(NULL);
}

int main(void)
{
	int *grades = malloc(10*sizeof(int));
	for(int i = 0; i < 10; i++)
	{
		printf("Enter grade: ");
		scanf("%d",&grades[i]);
	}
	pthread_t *pts = malloc(10*sizeof(pthread_t));
	pthread_mutex_init(&grade_mutex,NULL);
	for(int i = 0; i < 10; i++)
	{
		pthread_create(&pts[i],NULL,class_total,(void*)grades[i]);
	}

	printf("Total: %d", total_grade);
	pthread_mutex_destroy(&grade_mutex);
	pthread_exit(NULL);
}