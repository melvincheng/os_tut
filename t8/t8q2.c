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

typedef struct FIFO{
	proc process;
	struct FIFO *next;
} queue;

void push(queue **list, proc process);
proc *pop(queue **list);

int avail_mem[MEMORY] = { 0 };

int main(void){
	queue *priority = NULL;
	queue *secondary = NULL;
	FILE *fp;
	proc process, *temp_proc;
	pid_t pid;
	int status;
	fp = fopen("processes_q2.txt", "r");

	while(fscanf(fp, "%[^,], %d, %d, %d\n", process.name, &process.priority, &process.memory, &process.runtime) > 0){
		process.pid = 0;
		process.address = 0;
		if(process.priority == 0){
			push(&priority, process);
		}else{
			push(&secondary, process);
		}
	}
	temp_proc = pop(&priority);
	while(temp_proc != NULL){
		for(int i = 0; i < temp_proc->memory; i++){
			avail_mem[i] = 1;
		}
		temp_proc->address = 0;
		pid = fork();
		if(pid < 0){
			return 1;
		}else if(pid == 0){
			execl("process", NULL);
			return 0;
		}else{
			temp_proc->pid = pid;
			printf("%s %d %d %d %d\n", temp_proc->name, temp_proc->priority, temp_proc->pid, temp_proc->memory, temp_proc->runtime);
			sleep(temp_proc->runtime);
			kill(temp_proc->pid, SIGINT);
			waitpid(temp_proc->pid, &status, 0);
		}
		for(int i = 0; i < temp_proc->memory; i++){
			avail_mem[i] = 0;
		}
		temp_proc = pop(&priority);
	}

	temp_proc = pop(&secondary);
	while(temp_proc != NULL){
		if(temp_proc->pid != 0){
			pid = fork();
			if(pid < 0){
				return 1;
			}else if(pid == 0){
				execl("process", NULL);
			}else{
				printf("%s %d %d %d %d\n", temp_proc->name, temp_proc->priority, temp_proc->pid, temp_proc->memory, temp_proc->runtime);
				temp_proc->pid = pid;
				temp_proc->runtime--;
				temp_proc->suspended = true;
				push(&secondary, *temp_proc);
				kill(temp_proc->pid, SIGTSTP);
			}
		}else{
			if(temp_proc->runtime == 1){
				kill(temp_proc->pid, SIGCONT);
				sleep(temp_proc->runtime);
				kill(temp_proc->pid, SIGINT);
				waitpid(temp_proc->pid, &status, 0);
			}else{
				temp_proc->runtime--;
				kill(temp_proc->pid, SIGCONT);
				sleep(1);
				kill(temp_proc->pid, SIGTSTP);
				push(&secondary, *temp_proc);
			}
		}
		temp_proc = pop(&secondary);
	}
}

void push(queue **list, proc process){
	queue *temp_node, *current_node, *temp_list;

	temp_list = *list;

	current_node = (queue *) malloc(sizeof(queue));

	current_node->process = process;
	current_node->next = NULL;

	if(temp_list == NULL){
		temp_list = (queue *) malloc(sizeof(queue));
		temp_list->process = process;
		temp_list->next = NULL;
	} else if(temp_list->next == NULL){
		temp_list->next = current_node;
	} else {
		temp_node = temp_list->next;
		while(temp_node->next != NULL){
			temp_node = temp_node->next;
		}
		temp_node->next = current_node;
	}
	*list = temp_list;
}

proc *pop(queue **list){
	proc *proc_popped;
	queue *new_head, *temp_list;

	temp_list = *list;

	if(temp_list == NULL){
		return NULL;
	}

	new_head = *list;
	proc_popped = &temp_list->process;
	new_head = temp_list->next;
	// free(temp_list);

	*list = new_head;
	return proc_popped;
}