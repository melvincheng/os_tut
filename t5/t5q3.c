#define _XOPEN_SOURCE 600 // required for barriers to work

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 5

typedef struct{
	char name[256];
	int student_id;
	float grade;
} student;

void *bellcurve(void* stud);

int main(void){
	student students[5];
	pthread_t threads[NUM_THREAD];
	pthread_attr_t threads_attr[NUM_THREAD];

	for(int i = 0; i < 5; i++){
		printf("%s\n", "Please enter the student's name");
		scanf("%s", students[i].name);
		printf("%s\n", "Please enter the student's id");
		scanf("%d", &students[i].student_id);
		printf("%s\n", "Please enter the student's grade");
		scanf("%f", &students[i].grade);
	}
	for (int i = 0; i < 5; i++){
		pthread_attr_init(&threads_attr[i]);
		pthread_create(&threads[i], &threads_attr[i], bellcurve, (void*)&students[i]);
	}
	pthread_exit(NULL);
}

void *bellcurve(void* stud){
	student* person = (student*)stud;
	printf("Name: %s\nID: %d\nGrade:%f\n\n", person->name, person->student_id, person->grade*1.5);
}