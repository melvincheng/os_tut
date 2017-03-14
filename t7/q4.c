#define _POSIX_SOURCE
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	pid_t pid;
	int status;
	pid = fork();
	if(!pid)
	{
		execlp("./process", "./process",NULL);
	}
	printf("sleeping\n");
	sleep(5);
	printf("sending sigstop\n");
	kill(pid,SIGTSTP);
	sleep(10);
	kill(pid,SIGCONT);
	//process isn't terminating
	while((pid = wait(&status) > 0));
}