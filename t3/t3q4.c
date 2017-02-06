#include <stdio.h>
#include <stdlib.h>

int main(){
	char * professor;
	int *student_ids, *grades;
	int n;
	professor = (char*)calloc(256, sizeof(char));
	printf("Enter your name:\n");
	scanf("%s", professor);
	printf("Enter the number of students:\n");
	scanf("%d", &n);
	student_ids = (int*)malloc(n * sizeof(int));
	grades = (int*)malloc(n * sizeof(int));
	free(professor);
	free(student_ids);
	free(grades);
}