#define _XOPEN_SOURCE 600 // required for barriers to work
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int grade_total = 0;
float total_bellcurve = 0;
pthread_mutex_t grade_mutex;
pthread_barrier_t barrier;

void *read_grades()
{
	int *grades = malloc(10*sizeof(int));
	FILE* f;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	f = fopen("grades.txt", "r");
	int i = 0;
	pthread_mutex_lock(&grade_mutex);
	while ((read = getline(&line, &len, f)) != -1) 
	{
    	grades[i++] = atoi(line);
    }
    pthread_mutex_unlock(&grade_mutex);
    fclose(f);
    return grades;
}

void* save_bellcurve(void* grade)
{
	int g = (int)grade;
	FILE* f;
	pthread_mutex_lock(&grade_mutex);
	grade_total+=g;
	total_bellcurve+=g*1.5f;
	f = fopen("bellcurve.txt", "a");
	fprintf(f,"%f\n",g*1.5f);
	fclose(f);
	pthread_mutex_unlock(&grade_mutex);
	pthread_exit(NULL);
}

int main(void)
{
	int* grades = malloc(10*sizeof(int));
	pthread_mutex_init(&grade_mutex,NULL);
	pthread_barrier_init(&barrier,NULL,1);
	pthread_t reader;
	printf("Starting reader\n");
	pthread_create(&reader,NULL,read_grades,(void*)NULL);
	pthread_join(reader,(void**)&grades);
	pthread_barrier_wait(&barrier);
	pthread_t *pts = malloc(10*sizeof(pthread_t));
	for(int i = 0; i < 10; i++)
	{
		pthread_create(&pts[i],NULL,save_bellcurve,(void*)grades[i]);
	}

	printf("%f\n",total_bellcurve);
	pthread_exit(NULL);
}