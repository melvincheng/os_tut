#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
int main(int argc, char* argv[])
{
	int n = 100000000;
	double dx = 1/(n+1);
	double y[n];
	#ifdef _OPENMP
	omp_set_num_threads((int)argv[1]);
	#endif
	#pragma omp parallel
	{
		for(int i = 0; i < n; i++ )
		{
			double x = i*dx;
			#ifdef _OPENMP
			y[i] = exp(x) * cos(x) * sin(x) * sqrt(5*x + 6.0);
			#endif
		}
	}
	printf("Finished\n");
	return 0;
}