#include <stdio.h>
#include <omp.h>

int fibonacci_serial(int n) {
    if (n <= 1)
        return n;
    return fibonacci_serial(n - 1) + fibonacci_serial(n - 2);
}

int fibonacci_parallel(int n) {
    if (n <= 1)
        return n;
    int x, y;

    #pragma omp task shared(x)
    x = fibonacci_parallel(n - 1);

    #pragma omp task shared(y)
    y = fibonacci_parallel(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 30; 
    int result;
    double start_time, end_time, serial_time, parallel_time;

    // Measure serial Fibonacci execution time
    start_time = omp_get_wtime();
    result = fibonacci_serial(n);
    end_time = omp_get_wtime();
    serial_time = end_time - start_time;
    printf("Serial Fibonacci(%d) = %d, Time: %f seconds\n", n, result, serial_time);

    // Measure parallel Fibonacci execution time
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci_parallel(n);
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel Fibonacci(%d) = %d, Time: %f seconds\n", n, result, parallel_time);

    // Calculate and print speedup
    double speedup = serial_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}
