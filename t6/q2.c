#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int status = 0;
	pid = fork();
	if(!pid)
	{
		sleep(1);
		printf("Child process\n");
		exit(0);
	}

	while((pid = wait(&status)) > 0);
		printf("Parent process\n");
	return 0;
}