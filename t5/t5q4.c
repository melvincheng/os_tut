#define _XOPEN_SOURCE 600 // required for barriers to work

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 5

pthread_mutex_t total_grade_mutex;
float total_grade = 0;

void* class_total(void* grade);

int main(void){
	float grades[10];
	pthread_t threads[NUM_THREAD];
	pthread_attr_t threads_attr[NUM_THREAD];
	printf("%s\n", "Please enter 10 grades");
	for(int i = 0; i < 10; i++){
		scanf("%f", &grades[i]);
		pthread_attr_init(&threads_attr[i]);
		pthread_create(&threads[i], &threads_attr[i], class_total, (void*)&grades[i]);
	}
	pthread_exit(NULL);
	printf("%f\n", total_grade);
}

void* class_total(void* grade){
	pthread_mutex_lock(&total_grade_mutex);
	total_grade += *(float*)grade;
	pthread_mutex_unlock(&total_grade_mutex);
}