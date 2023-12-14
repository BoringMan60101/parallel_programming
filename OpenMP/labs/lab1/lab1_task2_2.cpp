#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    srand(time(nullptr));
    int n = 16; //shared by default
    int thr = 4; //threads numbers 
    int sum = 0; //sum of elements in A
    int A[n]{}; 
    int B[thr]{}; //array with partial sum

    //initialization values in target array A
    for(int i = 0; i < n; i++)
    {
        //A[i] = rand() % 6; //[0; 5]
        A[i] = 1; //[0; 5]
        printf("A[%i] = %i\n", i, A[i]);
    }

    #pragma omp parallel num_threads(thr)
    {
        int m = n / omp_get_num_threads();
        int thr_id = omp_get_thread_num();
        for(int i = 0; i < m; i++)
            B[thr_id] += A[thr_id*m + i];
    }

    //count sum of partial amounts (values of B[])
    printf("\n");
    for(int i = 0; i < thr; i++)
    {
        sum += B[i];
        printf("B[%i] = %i\n", i, B[i]);
    }

	//output result
    printf("\nSum elements in array A = %d\n", sum);

    return 0;
}
