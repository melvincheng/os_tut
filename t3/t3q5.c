#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	int student_id;
	int mark;
} grade;

void grade_students(grade * grades, int num_students);

int main(){
	char * professor;
	grade * grades;
	int num_students;
	professor = (char*)calloc(256, sizeof(char));
	printf("Enter your name:\n");
	scanf("%s", professor);
	printf("Enter the number of students:\n");
	scanf("%d", &num_students);
	grades = (grade*)malloc(num_students * sizeof(grade));
	for(int i = 0; i < num_students; i++){
		printf("Enter student ID:\n");
		scanf("%d", &grades[i].student_id);
		printf("Enter mark:\n");
		scanf("%d", &grades[i].mark);	
	}
	grade_students(grades, num_students);

	free(professor);
	free(grades);
}

void grade_students(grade * grades, int num_students){
	FILE *fp;
	fp = fopen("grades.txt", "w");
	int sum = 0;
	float average, std_dev, variance, dev_sum = 0.0;
	for(int i = 0; i < num_students; i++){
		sum += grades[i].mark;
		fprintf(fp, "%d,%d\n", grades[i].student_id, grades[i].mark);
	}

	average = (float)sum/(float)num_students;
	for(int i = 0; i < num_students; i++){
		dev_sum += pow((grades[i].mark - average),2);
	}

	variance = (float)dev_sum/(float)num_students;
	std_dev = sqrt(variance);
	fprintf(fp, "%f,%f\n", average, std_dev);
	fclose(fp);
}