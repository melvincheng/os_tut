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
proc *pop();	
proc *delete_name(char *name);
proc *delete_pid(int pid);

int main(void){
	FILE *fp;
	proc temp_process, *removed_proc;
	struct queue *temp;
	int status;
	pid_t pid;
	fp = fopen("processes_q5.txt", "r");
	for(int i = 0; i < 10; i++){
		fscanf(fp, "%[^,], %d, %d\n", temp_process.name, &temp_process.priority, &temp_process.runtime);
		temp_process.pid = 0;
		// printf("%s %d %d %d\n", temp_process.name, temp_process.priority, temp_process.pid, temp_process.runtime);
		push(temp_process);
	}
	fclose(fp);

	temp = list;
	while(temp != NULL){
		if(temp->process.priority == 0){
			pid = fork();
			if(pid < 0){
				return 1;
			} else if(pid == 0){
				execl("process", NULL);
			} else {
				temp->process.pid = pid;
				sleep(temp->process.runtime);
				kill(pid, SIGINT);
				waitpid(pid, &status, 0);
				removed_proc = delete_name(temp->process.name);
				printf("Name: %s\n Priority: %d\n Pid: %d\n Runtime: %d\n\n", removed_proc->name, removed_proc->priority, removed_proc->pid, removed_proc->runtime);
			}
		}
		temp = temp->next;
	}

	temp = list;
	while(temp != NULL){
		pid = fork();
		if(pid < 0){
			return 1;
		} else if(pid == 0){
			execl("process", NULL);
		} else {
			temp->process.pid = pid;
			sleep(temp->process.runtime);
			kill(pid, SIGINT);
			waitpid(pid, &status, 0);
			removed_proc = pop();
			printf("Name: %s\n Priority: %d\n Pid: %d\n Runtime: %d\n\n", removed_proc->name, removed_proc->priority, removed_proc->pid, removed_proc->runtime);
		}
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

proc *pop(){
	proc *proc_popped;
	struct queue *new_head;

	if(list == NULL){
		return NULL;
	}

	new_head = list;

	proc_popped = &list->process;
	// free(list);
	list = new_head->next;
	return proc_popped;
}

proc *delete_name(char *name){
	proc *proc_delete;
	struct queue *temp_node, *prev_node;

	if(strcmp(list->process.name, name) == 0){
		return pop();
	}

	temp_node = list;
	while(temp_node != NULL){
		if(strcmp(temp_node->process.name, name) == 0){
			prev_node->next = temp_node->next;
			proc_delete = &temp_node->process;
			// free(temp_node);
			return proc_delete;
		}
		prev_node = temp_node;
		temp_node = temp_node->next;
	}
	return NULL;
}

proc *delete_pid(int pid){
	proc *proc_delete;
	struct queue *temp_node, *prev_node;

	if(list->process.pid == pid){
		return pop();
	}

	temp_node = list;
	while(temp_node != NULL){
		if(temp_node->process.pid == pid){
			prev_node->next = temp_node->next;
			proc_delete = &temp_node->process;
			// free(temp_node);
			return proc_delete;
		}
		prev_node = temp_node;
		temp_node = temp_node->next;
	}
	return NULL;
}