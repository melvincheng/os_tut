#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define dimension 100

int main(void){
	int temp;
	int a[dimension][dimension];
	int b[dimension][dimension];
	int result[dimension][dimension];

	omp_set_num_threads(4);

	for(int i = 0; i < dimension; i++){
		for(int j = 0; j < dimension; j++){
			a[i][j] = i + j;
			b[i][j] = i - j;
		}
	}

	printf("Matrix A: \n");
	for(int m = 0; m < dimension; m++){
		for(int n = 0; n < dimension; n++){
			printf("%d ", a[m][n]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Matrix B: \n");
	for(int m = 0; m < dimension; m++){
		for(int n = 0; n < dimension; n++){
			printf("%d ", b[m][n]);
		}
		printf("\n");
	}
	printf("\n");

	for(int m = 0; m < dimension; m++){
		for(int n = 0; n < dimension; n++){
			temp = 0;
			#pragma omp parallel for reduction(+:temp)
			for(int k = 0; k < dimension; k++){
				temp += a[m][k] * b[k][n];
			}
			result[m][n] = temp;
		}
	}

	printf("Result: \n");
	for(int m = 0; m < dimension; m++){
		for(int n = 0; n < dimension; n++){
			printf("%d ", result[m][n]);
		}
		printf("\n");
	}
}