#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void child1()
{
	FILE* f = fopen("child1.txt","w");
	fprintf(f, "child1\n");
	fclose(f);

	sleep(1);

	int read;
	size_t len = 0;
	char* line = NULL;
	f = fopen("child1.txt", "r");
	if(f)
	{
		while((read = getline(&line, &len,f)) != -1)
			printf("%s",line);
	}
	fclose(f);
}

void child2()
{
	FILE* f = fopen("child2.txt","w");
	fprintf(f, "child2\n");
	fclose(f);

	sleep(1);

	int read;
	size_t len = 0;
	char* line = NULL;
	f = fopen("child2.txt", "r");
	if(f)
	{
		while((read = getline(&line, &len,f)) != -1)
			printf("%s",line);
	}
	fclose(f);
}

int main(void)
{
	pid_t pid;
	pid = fork();
	if(!pid)
	{
		child2();
	}
	else if(pid)
	{
		child1();
	}
	else
	{
		printf("Error forking\n");
	}

	return 0;
}