#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(void){
	int x[100000000];
	float norm = 0;
	double start;
	struct timeval;

	omp_set_num_threads(4);

	for(int i = 0; i < 100000000; i++){
		x[i] = rand() % 100;
	}


	start = omp_get_wtime();
	for(int i = 0; i < 100000000; i++){
		norm += fabs(x[i]);
	}
	printf("Serial: %lf\n", omp_get_wtime() - start);

	norm = 0;


	start = omp_get_wtime();
	#pragma omp parallel reduction(+:norm)
	{
		for(int i = 0; i < 100000000; i++){
			norm += fabs(x[i]);
		}
	}
	printf("OpenMP: %lf\n", omp_get_wtime() - start);


}