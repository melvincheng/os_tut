#define _XOPEN_SOURCE 600 // required for barriers to work

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

void *hello_world();
void *goodbye();

int main(void)
{
	pthread_t threads[NUM_THREADS];
	pthread_attr_t threads_attr[NUM_THREADS];
	pthread_attr_init(&threads_attr[0]);
	pthread_attr_init(&threads_attr[1]);
	pthread_create(&threads[0], &threads_attr[0], hello_world, NULL);
	pthread_create(&threads[1], &threads_attr[1], goodbye, NULL);
	pthread_exit(NULL);
}

void *hello_world(){
	sleep(rand()%1);
	printf("hello world\n");
}

void *goodbye(){
	sleep(rand()%1);
	printf("goodbye\n");
}