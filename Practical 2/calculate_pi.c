#include <stdio.h>
#include <omp.h>

int main() {
    long num_steps = 1000000000;
    double step = 1.0 / (double)num_steps;
    double sum = 0.0;
    double start_time, end_time, serial_time, parallel_time;

    // Serial calculation of Pi
    start_time = omp_get_wtime();
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    double pi_serial = step * sum;
    end_time = omp_get_wtime();
    serial_time = end_time - start_time;
    printf("Serial calculation of Pi: %.15f\n", pi_serial);
    printf("Serial Execution Time: %f seconds\n", serial_time);

    sum = 0.0;  // Reset sum for parallel calculation

    // Parallel calculation of Pi
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction(+:sum)
        for (int i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    }
    double pi_parallel = step * sum;
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel calculation of Pi: %.15f\n", pi_parallel);
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    // Calculate speedup
    double speedup = serial_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}
