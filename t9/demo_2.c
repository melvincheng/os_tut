#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;
    // only executes the block if _OPENMP is some defined header,
    // which is defined when using -fopenmp
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    // defines a parallel region of code that will be executed by 
    // each thread in parallel
    #pragma omp parallel
    {
        //defines the critical section of the parallel region
        #pragma omp critical
        {
            #ifdef _OPENMP
            num += 1; // THREAD SAFE INCREMENT
            thread_num = omp_get_thread_num();
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }
    return 0;
}
