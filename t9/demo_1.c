#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    printf("This statement will always print.\n");
    // Code after the ifdef will only execute if the program is compiled with the openmp flag
    #ifdef _OPENMP
    printf("This statement will only print when compiled with \"-fopenmp\"\n");
    #endif
    return 0;
}