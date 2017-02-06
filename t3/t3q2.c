#include <stdlib.h>
#include <stdio.h>

int main(void){
	FILE *fp;
	int array[10];
	fp = fopen("question2.txt", "r");
	for(int i = 0; fscanf(fp, "%d", &array[i]) > 0; i++){
		printf("%d\n", array[i]);
	}
	fclose(fp);
}