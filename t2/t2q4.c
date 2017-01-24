#include <stdio.h>
int main(void){
	for(int i = 1 ; i < 11 ; i++){
		if(i%2 == 0){
			printf("even\n");
		} else if(i%2 == 1){
			printf("odd\n");
		}
	}
}