#define _XOPEN_SOURCE 600 // required for barriers to work

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 5

void *bellcurve(void *grade);

int main(void){
	float students[5];
	pthread_t threads[5];
	pthread_attr_t threads_attr[5];
	printf("Enter the grade of 5 students\n");
	for(int i = 0; i < 5; i++){
		scanf("%f", &students[i]);
	}
	for(int i = 0; i < 5; i++){
		pthread_attr_init(&threads_attr[i]);
		pthread_create(&threads[i], &threads_attr[i], bellcurve, (void*)&students[i]);
	}
	pthread_exit(NULL);
}

void *bellcurve(void *grade){
	printf("%f\n", *(float*)grade*1.5);
}