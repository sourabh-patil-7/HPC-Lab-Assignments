#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void matrix_addition(int n, int num_threads, double *serial_time) {
    int A[n][n], B[n][n], C[n][n];

    // Initialize matrices A and B
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    // Measure the start time for parallel or serial run
    double start_time = omp_get_wtime();

    // Parallel matrix addition
    #pragma omp parallel for num_threads(num_threads) collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Measure the end time
    double end_time = omp_get_wtime();
    double exec_time = end_time - start_time;

    if (num_threads == 1) {
        *serial_time = exec_time;  // Store serial time for speedup calculation
    }

    printf("Time taken for matrix addition with size %d and %d threads: %f seconds\n", n, num_threads, exec_time);

    if (num_threads > 1) {
        double speedup = *serial_time / exec_time;
        printf("Speedup with %d threads: %f\n", num_threads, speedup);
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_threads[] = {1, 2, 4, 8};
    double serial_time = 0.0;

    // Loop through different matrix sizes
    for (int i = 0; i < 5; i++) {
        printf("\nMatrix size: %d\n", sizes[i]);

        // Loop through different numbers of threads
        for (int j = 0; j < 4; j++) {
            matrix_addition(sizes[i], num_threads[j], &serial_time);
        }
    }

    return 0;
}
