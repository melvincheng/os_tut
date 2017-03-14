#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		return 1;
	}else if(pid == 0){
		execl("process", NULL);
	}else{
		sleep(5);
		kill(pid, SIGINT);
	}
}