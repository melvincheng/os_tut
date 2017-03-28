#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;
    // Code after the ifdef will only execute if the program is compiled with the openmp flag
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    // Code after this pragma will run in parallel with multiple threads
    #pragma omp parallel
    {
        // The block of code after this pragma is in a critical section. This means only one thread can access this block of code at a time
        #pragma omp critical
        {
            // Code after the ifdef will only execute if the program is compiled with the openmp flag
            #ifdef _OPENMP
            num += 1; // THREAD SAFE INCREMENT
            thread_num = omp_get_thread_num();
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }
    return 0;
}