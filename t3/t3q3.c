#include <stdlib.h>
#include <stdio.h>

#define BUFFER 256

typedef struct{
	int student_id;
	int age;
	int year;
} student;

void save_student(student stu);

int main(void){
	student stu;
	char buffer[BUFFER];
	printf("%s\n", "Enter your student id");
	scanf("%d", &stu.student_id);
	printf("%s\n", "Enter your age");
	scanf("%d", &stu.age);
	printf("%s\n", "Enter your starting year");
	scanf("%d", &stu.year);
	save_student(stu);
}

void save_student(student stu){
	FILE *fp;
	fp = fopen("student.txt", "a");
	fprintf(fp, "%d,%d,%d\n", stu.student_id, stu.age, stu.year);
	fclose(fp);
}