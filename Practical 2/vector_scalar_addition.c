#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 1000000; 
    int scalar = 5;  
    int vector[n];
    double start_time, end_time, serial_time, parallel_time;

    for (int i = 0; i < n; i++)
    {
        vector[i] = i;
    }

    start_time = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        vector[i] = i; 
        vector[i] += scalar;
    }
    end_time = omp_get_wtime();
    serial_time = end_time - start_time;
    printf("Serial Execution Time: %f seconds\n", serial_time);


    for (int i = 0; i < n; i++)
    {
        vector[i] = i;
    }


    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        vector[i] += scalar;
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel Execution Time: %f seconds\n", parallel_time);


    double speedup = serial_time / parallel_time;
    printf("Speedup: %f\n", speedup);


    for (int i = 0; i < 10; i++)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");

    return 0;
}
