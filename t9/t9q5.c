#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char argv[]){
	if(argc < 2){
		fprintf(stderr, "Not enough arguments\n");
		exit(-1);
	}

	double x;
	int n = 100000000;
	double y[100000000];
	double dx = 1.0 / ((double)n+1.0);
	FILE *fp;

	fp = fopen("calculations.txt", "w");

	omp_set_num_threads(argv[1]);
	#pragma omp parallel for private(x)
	for(int i = 0; i < n; i++){
		x = i * dx;
		y[i] = exp(x) * cos (x) * sin (x) * sqrt (5 * x + 6.0);
		if(i%1000000 == 0){
			#pragma omp critical
			{
				fprintf(fp, "%d %lf %lf\n", i, x, y[i]);
			}
		}
	}

}