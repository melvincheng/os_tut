#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
int main(int argc, char* argv[])
{
	srand(time(NULL));
	int x[100000000];
	for(int i = 0; i < sizeof(x)/4; i++)
		x[i] = rand()%101;
	int norm;
	double start = omp_get_wtime();
	for(int i = 0; i < sizeof(x)/4; i++)
		norm+= fabs(x[i]);
	double end = omp_get_wtime();
	printf("Serial took: %f\n",end-start);
	norm = 0;
	int nthreads = 16;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
	start = omp_get_wtime();
	#pragma omp parallel for reduction(+: norm)
	for(int i = 0; i < sizeof(x)/4; i++)
		norm+= fabs(x[i]);
	end = omp_get_wtime();
	printf("Parallel took: %f\n",end-start);
	//Parallel generally ~.5 seconds faster
	return 0;
}