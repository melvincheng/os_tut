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

struct queue *list = NULL;

void push(proc process);

int main(void){
	FILE *fp;
	proc temp_process;

	

	fp = fopen("processes.txt", "r");
	for(int i = 0; i < 10; i++){
		fscanf(fp, "%[^,], %d, %d, %d\n", temp_process.name, &temp_process.priority, &temp_process.pid, &temp_process.runtime);
		// printf("%s %d %d %d\n", temp_process.name, temp_process.priority, temp_process.pid, temp_process.runtime);
		push(temp_process);
	}
	fclose(fp);

	struct queue *temp;
	temp = list;
	while(temp != NULL){
		printf("Name: %s\n Priority: %d\n Pid: %d\n Runtime: %d\n\n", temp->process.name, temp->process.priority, temp->process.pid, temp->process.runtime);
		temp = temp->next;
	}
}

void push(proc process){
	struct queue *temp_node, *current_node;

	current_node = (struct queue *) malloc(sizeof(struct queue));

	current_node->process = process;
	current_node->next = NULL;

	if(list == NULL){
		list = (struct queue *) malloc(sizeof(struct queue));
		list->process = process;
		list->next = NULL;
	} else if(list->next == NULL){
		list->next = current_node;
	} else {
		temp_node = list->next;
		while(temp_node->next != NULL){
			temp_node = temp_node->next;
		}
		temp_node->next = current_node;
	}
}

