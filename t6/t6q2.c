#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int main(void){
	pid_t pid;
	pid = fork();
	int status;

	if(pid < 0){
		return 1;
	}else if(pid == 0){
		sleep(1);
		printf("Child process\n");
	}else{
		wait(&status);
		printf("Parent process\n");
		printf("%d\n", status);
	}
	return 0;
}