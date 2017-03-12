#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct 
{
	char name[256];
	int priority;
	int pid;
	int runtime;
}proc;

typedef struct queue
{
	proc process;
	struct queue* next;

}Queue;

void push(Queue* q, proc process)
{
	Queue* curr = q;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = malloc(sizeof(Queue));
	curr->next->process = process;
	curr->next->next = NULL;
}

proc pop(Queue* q)
{
	proc p;
	if(q->next == NULL)
	{
		sleep(10);
		p = q->process;
		//setting q to NULL doesnt terminate the pop loop
		//for some reason, only results in systmd being 
		//popped constantly
		free(q);
	}
	else
	{
		Queue* curr = q;
		while(curr->next->next != NULL)
		{
			printf("%s->",curr->process.name);
			curr = curr->next;
		}
		printf("\nsecond last process is %s",curr->process.name);
		p = curr->next->process;
		curr->next = NULL;
	}
	printf("\npopping %s\n",p.name);
	return p;
}

proc delete_name(Queue* q, char* name)
{
	proc p;
	Queue* curr = q;
	while(strcmp(curr->next->process.name,name) != 0)
		curr = curr->next;
	Queue* todelete = curr->next;
	curr->next = todelete->next;
	p = todelete->process;
	todelete = NULL;
	return p;
}

proc delete_pid(Queue* q, int pid)
{
	proc p;
	Queue* curr = q;
	while(curr->next->process.pid != pid)
		curr = curr->next;
	Queue* todelete = curr->next;
	curr->next = todelete->next;
	p = todelete->process;
	todelete = NULL;
	return p;
}

void printqueue(Queue* q)
{
	if(q == NULL)
		printf("Queue is empty.\n");
	else
	{
		Queue* curr = q;
		while(curr->next != NULL)
		{
			printf("Process: %s\n",curr->process.name);
			printf("Priority: %d\n",curr->process.priority);
			printf("PID: %d\n",curr->process.pid);
			printf("Runtime: %d\n", curr->process.runtime);
			curr=curr->next;
			printf("\n");
		}
		printf("Process: %s\n",curr->process.name);
		printf("Priority: %d\n",curr->process.priority);
		printf("PID: %d\n",curr->process.pid);
		printf("Runtime: %d\n", curr->process.runtime);
		printf("\n");
	}
}

int main(void)
{
	Queue* q = NULL;
	FILE* f = fopen("processes.txt", "r");
	const char s[2] = ", ";
	char* token;
	if(f != NULL)
	{
		char line[30];
		while(fgets(line,sizeof(line), f) != NULL)
		{
			token = strtok(line,s);
			proc p;
			for(int i = 0; i < 4; i++)
			{
				if(i == 0)
				{
					strcpy(p.name,token);
					token = strtok(NULL,s);
				}
				else if(i == 1)
				{
					p.priority = atoi(token);
					token = strtok(NULL,s);
				}
				else if(i == 2)
				{
					p.pid = atoi(token);
					token = strtok(NULL,s);
				}
				else
					p.runtime = atoi(token);
			}
			if(q == NULL)
			{
				q = malloc(sizeof(Queue));
				q->process = p;
				q->next = NULL;
			}
			else
				push(q,p);
		}
	}
	fclose(f);
	delete_name(q,"emacs");
	delete_pid(q,12235);
	while(q != NULL)
	{

		printf("is q null: %d\n",q == NULL);
		proc p = pop(q);
		printf("Process: %s\n",p.name);
		printf("Priority: %d\n",p.priority);
		printf("PID: %d\n",p.pid);
		printf("Runtime: %d\n",p.runtime);
		printf("\n");
	}
}