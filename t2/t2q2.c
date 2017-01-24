#include <stdio.h>
int main(void){
	double array[5] = {1.2,5.5,2.1,3.3,3.3};
	for(int i = 1 ; i < 5 ; i++){
		if(array[i] < array[i-1]){
			printf("less than\n");
		} else if(array[i] > array[i-1]){
			printf("greater than\n");
		} else if(array[i] == array[i-1]){
			printf("the same\n");
		}
	}
}