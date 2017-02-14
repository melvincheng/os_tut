#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct
{
	char name[256];
	int student_id;
	int grade;
}student;

void *bellcurve(void *stud)
{
	student s = *((student*)stud);

	printf("Name: %s\nID: %d\n",s.name,s.student_id);
	printf("Bellcurve: %f\n", s.grade*1.5f);
	pthread_exit(NULL);
}

int main(void)
{
	student *students = malloc(5*sizeof(int));
	char string[256];
	for(int i = 0; i < 5; i++)
	{
		printf("Enter name: ");
		scanf("%s", string);
		strcpy(students[i].name,string);
		printf("Enter student id: ");
		scanf("%d",&students[i].student_id);
		printf("Enter grade: ");
		scanf("%d",&students[i].grade);
	}

	pthread_t *pts = malloc(5*sizeof(pthread_t));
	for(int i = 0; i < 5; i++)
	{
		pthread_create(&pts[i],NULL,bellcurve,(void*)&students[i]);
	}

	pthread_exit(NULL);
}