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

Queue* q;

void push(proc process)
{
	Queue* curr = q;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = malloc(sizeof(Queue));
	curr->next->process = process;
	curr->next->next = NULL;
}


proc pop()
{
	proc p;
	if(q->next == NULL)
	{
		p = q->process;
		//setting q to NULL doesnt terminate the pop loop
		//for some reason, only results in systmd being 
		//popped constantly
		q = NULL;
	}
	else
	{
		Queue* head = q->next;
		p = q->process;
		q = NULL;
		q = head;
	}
	printf("\npopping %s\n",p.name);
	return p;
}

proc delete_name(char* name)
{
	proc p;
	printf("deleting %s\n",name);
	if(strcmp(q->process.name,name) == 0)
	{
		Queue* next = q->next;
		p = q->process;
		q = next;
		printf("deleted %s\n",p.name);
	}
	else
	{
		Queue* curr = q;
		while(strcmp(curr->next->process.name,name) != 0)
			curr = curr->next;
		Queue* todelete = curr->next;
		curr->next = todelete->next;
		p = todelete->process;
		todelete = NULL;
		printf("deleted %s\n", p.name);
	}
	return p;
}

proc delete_pid(int pid)
{
	proc p;
	printf("deleting %d\n",pid);
	if(q->process.pid == pid)
	{
		Queue* next = q->next;
		p = q->process;
		q = next;
		printf("deleted %s\n",p.name);
	}
	else
	{
		Queue* curr = q;
		while(curr->next->process.pid != pid)
			curr = curr->next;
		Queue* todelete = curr->next;
		curr->next = todelete->next;
		p = todelete->process;
		todelete = NULL;
	}
	return p;
}

void printqueue()
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
	q = NULL;
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
				push(p);
		}
	}
	fclose(f);
	delete_name("emacs");
	delete_pid(12235);
	while(q != NULL)
	{
		proc p = pop();
		printf("Process: %s\n",p.name);
		printf("Priority: %d\n",p.priority);
		printf("PID: %d\n",p.pid);
		printf("Runtime: %d\n",p.runtime);
		printf("\n");
	}
}