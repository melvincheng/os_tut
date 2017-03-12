#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_LEN 256

int main(void){
	pid_t pid[2];

	FILE *file1;
	FILE *file2;

	char string[BUFFER_LEN];
	pid[0] = fork();
	if(pid[0] < 0){
		return 1;
	}else if(pid[0] == 0){
		sleep(1);
		file1 = fopen("child1.txt", "r");	
		fscanf(file1, "%s", string);
		printf("%s\n", string);
		fclose(file1);
	}else{
		pid[1] = fork();
		if(pid[1] < 0){
			return 1;
		}else if(pid[1] == 0){
			sleep(1);
			file2 = fopen("child2.txt", "r");	
			fscanf(file2, "%s", string);
			printf("%s\n", string);
			fclose(file2);
		}else{
			file1 = fopen("child1.txt", "w");
			file2 = fopen("child2.txt", "w");
			fprintf(file1, "child1\n");
			fprintf(file2, "child2\n");
			fclose(file1);
			fclose(file2);
		}
	}
	return 0;
}