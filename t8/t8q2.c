#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MEMORY 1024

typedef struct{
	char name[256];
	int priority;
	int pid;
	int address;
	int memory;
	int runtime;
	bool suspended;
} proc;

int main(void){
	int avail_mem length[MEMORY] = { 0 };
}