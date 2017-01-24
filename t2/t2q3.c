#include <stdio.h>
int main(void){
	char array[11] = {'h','e','l','l','o',' ','w','o','r','l','d'};
	int i;
	while(array[i]){
		printf("%c", array[i]);
		i++;
	}
	printf("\n");
}