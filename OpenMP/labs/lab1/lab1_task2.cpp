#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    srand(time(nullptr));
    int n = 2;
    int thr = 4;
    int sum = 0;
    int A[n*thr]{};
    int B[thr]{};

    //initialization values in target array A
    for(int i = 0; i < n*thr; i++)
    {
        //A[i] = rand() % 6; //[0; 5]
        A[i] = 1; //[0; 5]
        printf("A[%i] = %i\n", i, A[i]);
    }

    #pragma omp parallel num_threads(thr)
    {
        int thr_id = omp_get_thread_num();
        for(int i = 0; i < n; i++)
            B[thr_id] += A[thr_id*n + i];
    }

    //count sum of partial amounts (values of B[])
    printf("\n");
    for(int i = 0; i < thr; i++)
    {
        sum += B[i];
        printf("B[%i] = %i\n", i, B[i]);
    }

    //output results
    printf("\nSum elements in array A = %d\n", sum);

    return 0;
}
