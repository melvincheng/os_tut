#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{
	char parent[256];
	char name[256];
	int priority;
	int memory;
} proc;

typedef struct{
	proc *parent;
	proc *children;
	proc process;
} proc_tree;


int main(void){
	FILE *fp;
	fp = fopen("processes_tree.txt", "r");
	proc temp_proc;

	while(fscanf(fp, "%[^,], %[^,], %d, %d\n", temp_proc.parent, temp_proc.name, temp_proc, priority, temp_proc.memory) != 0){
		
	}
	


}