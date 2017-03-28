#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
int main(int argc, char* argv[])
{
	int size = 100;
	int a[size][size];
	int b[size][size];
	int c[size][size];
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			a[i][j] = j;
			b[i][j] = j;
		}
	int nthreads = 16;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    #pragma omp parallel
    {
    	
    	for(int i = 0; i < size; i++)
    	{
    		for(int j = 0; j < size; j++)
    		{
    			int dot = 0;
    			for(int k = 0; k < size; k++)
    			{
	    			dot+= a[i][k]*b[k][j];
	    			#pragma omp critical
	    			{
	    				c[i][j] = dot;
	    			}
	    		}
    		}
    	}
    }
}