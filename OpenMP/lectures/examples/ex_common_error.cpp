//В этой версии задаётся число элементов в частичной сумме
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main() {
    srand(time(nullptr));
    int n = 20000;
    int thr = 3; //кол-во потоков
    int sum = 0;
    int A[n*thr]{}; //массив значений
    
    for(int i = 0; i < n*thr; i++)
    {
        A[i] = 1; //[0; 5]
        printf("A[%i] = %i\n", i, A[i]);
    }
    
    #pragma omp parallel num_threads(thr)
    {
        int thr_id = omp_get_thread_num();
        for(int i = 0; i < n; i++)
            sum += A[thr_id*n + i];
    }
    
    printf("\nSum elements in array A = %d\n", sum);
    
    return 0;
}
