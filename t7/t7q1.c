#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{
	char name[256];
	int priority;
	pid_t pid;
	int runtime;
} proc;

struct queue{
	proc process;
	struct queue *next;
};

struct queue list = {.next = NULL};

void push(proc *process);

int main(void){
	FILE *fp;
	proc temp_process;
	fp = fopen("processes.txt", "r");
	for(int i = 0; i < 10; i++){
		fscanf(fp, "%[^,], %d, %d, %d\n", temp_process.name, &temp_process.priority, &temp_process.pid, &temp_process.runtime);
		// printf("%s %d %d %d\n", temp_process.name, temp_process.priority, temp_process.pid, temp_process.runtime);
		push(&temp_process);
	}
	fclose(fp);

	struct queue *temp;
	temp = &list;
	printf("%s %d %d %d\n", list.next->process.name, list.next->process.priority, list.next->process.pid, list.next->process.runtime);
	for(int i = 0; i < 10; i++){
		// printf("Name: %s, Priority: %d, Pid: %d, Runtime: %d\n", temp->process.name, temp->process.priority, temp->process.pid, temp->process.runtime);
		temp = temp->next;
	}
}

void push(proc *process){
	struct queue *temp_node;
	struct queue current_node = {.process = *process, .next = NULL};
	int count = 0;
	if(strcmp(list.process.name, "") == 0){
		list.process = *process;
	} else if(list.next == NULL){
		list.next = &current_node;
	}
	// } else {
	// 	temp_node = list.next;
	// 	while(temp_node->next != NULL){
	// 		temp_node = temp_node->next;
	// 	}
	// 	temp_node->next = &current_node;
	// }
}