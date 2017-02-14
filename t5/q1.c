#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void *hello_world()
{
	srand(time(NULL));
	sleep(rand()%10);
	printf("Hello world.\n");
	pthread_exit(NULL);
}

void *goodbye()
{
	srand(time(NULL));
	sleep(rand()%10);
	printf("Goodbye.\n");
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t t1, t2;
	pthread_create(&t1,NULL,hello_world,(void*)NULL);
	pthread_create(&t2,NULL,goodbye,(void*)NULL);

	pthread_exit(NULL);
}