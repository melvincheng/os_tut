#define _XOPEN_SOURCE 600 // required for barriers to work

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 5

void *bellcurve(void *grade);

int main(void){
	float students[5];
	pthread_t threads[NUM_THREAD];
	printf("Enter the grade of 5 students\n");
	for(int i = 0; i < 5; i++){
		scanf("%f", &students[i]);
	}
	for(int i = 0; i < NUM_THREAD; i++){
		pthread_create(&threads[i], NULL, bellcurve, (void*)&students[i]);
	}
	for(int i = 0; i < NUM_THREAD; i++){
		pthread_join(threads[i], NULL);
	}
}

void *bellcurve(void *grade){
	printf("%f\n", *(float*)grade*1.5);
}