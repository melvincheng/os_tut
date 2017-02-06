#include <stdio.h>
int main(void){
	char array[] = "hello world";
	for(int i = 0;;i++){
		if(array[i] == '\0'){
			break;
		}
		printf("%c", array[i]);

	}
	printf("\n");
}