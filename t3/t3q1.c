#include <stdlib.h>
#include <stdio.h>

#define BUFFER 256

int main(void){
	char first_name[BUFFER], age[BUFFER], height[BUFFER];
	printf("%s\n", "Enter your first name");
	scanf("%s", first_name);
	printf("%s\n", "Enter your age");
	scanf("%s", age);
	printf("%s\n", "Enter your height");
	scanf("%s", height);
	printf("First name: %s\n", first_name);
	printf("Age: %s\n", age);
	printf("Height: %s\n", height);
}