#define _XOPEN_SOURCE 600 // required for barriers to work

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 10

pthread_mutex_t total_grade_mutex;
float total_grade = 0;

void* class_total(void* grade);

int main(void){
	float grades[10];
	pthread_t threads[NUM_THREAD] = {0};
	printf("%s\n", "Please enter 10 grades");
	for(int i = 0; i < 10; i++){
		scanf("%f", &grades[i]);
		pthread_create(&threads[i], NULL, class_total, (void*)&grades[i]);
	}
	for(int i = 0; i < NUM_THREAD; i++){
		pthread_join(threads[i], NULL);
	}
	printf("Total grade: %f\n", total_grade);
}

void* class_total(void* grade){
	pthread_mutex_lock(&total_grade_mutex);
	total_grade += *(float*)grade;
	pthread_mutex_unlock(&total_grade_mutex);
}