#define _XOPEN_SOURCE 600 // required for barriers to work

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 10

pthread_mutex_t total_grade_mutex;
pthread_mutex_t total_bellcurve_mutex;
pthread_barrier_t read_barrier;
pthread_barrier_t calculate_barrier;
float total_grade = 0;
float total_bellcurve = 0;
float grades[10];

void * save_bellcurve(void * grade);
void * read_grades();

int main(void){
	pthread_t tid[NUM_THREAD];
	pthread_barrier_init(&read_barrier, NULL, 2);

	pthread_create(&tid[0], NULL, read_grades, NULL);
	pthread_barrier_wait(&read_barrier);
	pthread_barrier_init(&calculate_barrier, NULL, NUM_THREAD + 1);
	for(int i = 0; i < NUM_THREAD; i++){
		pthread_create(&tid[i], NULL, save_bellcurve, (void*)&grades[i]);
	}

	pthread_barrier_wait(&calculate_barrier);

	for(int i = 0; i < NUM_THREAD; i++){
		pthread_join(tid[i], NULL);
	}

	printf("Total grade: %f\n", total_grade);
	printf("Average before bellcurve: %f\n", total_grade/10);
	printf("Average after bellcurve: %f\n", total_bellcurve/10);

	pthread_barrier_destroy(&read_barrier);
}

void * save_bellcurve(void * grade){
	FILE *fp;
	fp = fopen("bellcurve.txt", "a");
	float bellcurve;

	pthread_mutex_lock(&total_grade_mutex);
	total_grade += *(float*)grade;
	pthread_mutex_unlock(&total_grade_mutex);

	pthread_mutex_lock(&total_bellcurve_mutex);
	bellcurve = *(float*)grade * 1.5;
	total_bellcurve += bellcurve;
	fprintf(fp, "%f\n", bellcurve);
	pthread_mutex_unlock(&total_bellcurve_mutex);
	fclose(fp);
	pthread_barrier_wait(&calculate_barrier);
}

void * read_grades(){
	FILE *fp;
	float grade;
	int i = 0;
	fp = fopen("grades.txt", "r");
	while(fscanf(fp, "%f", &grade) > 0){
		grades[i++] = grade;
	}
	pthread_barrier_wait(&read_barrier);
	fclose(fp);
	pthread_exit(NULL);
}